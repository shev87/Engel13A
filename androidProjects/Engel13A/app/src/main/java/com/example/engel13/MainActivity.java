package com.example.engel13;

import android.content.Context;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class MainActivity extends AppCompatActivity {

    Button startButton;
    TextView textView;

    static ArrayList<String> listUSB = new ArrayList<>();

    static {
        listUSB.add("UsbDriveA");
        listUSB.add("USBstorage1");
        listUSB.add("usbdisk");
        listUSB.add("usbotg");
        listUSB.add("UDiskA");
        listUSB.add("usb-storage");
        listUSB.add("usbcard");
        listUSB.add("usb");
    }

    String s = "";
    String fileSourceName = "/storage";
    File file;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        /**
         //check for permission
         if (ContextCompat.checkSelfPermission(this,
         Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED) {
         //ask for permission
         requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, READ_EXTERNAL_STORAGE_PERMISSION_CODE);
         }
         */

        startButton = findViewById(R.id.startButton);
        textView = findViewById(R.id.textView);
        View.OnClickListener onClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (searchFile() == 0) {
                    if (copyMachineData() == 0) {
                        changeMachineData();
                    }
                }
            }
        };
        startButton.setOnClickListener(onClickListener);
    }

    private int searchFile() {
        file = new File(fileSourceName + "/UsbDriveA/DATA/MACHINEDATA.TT.ZIP");
//        file = new File(fileSourceName + "/extSdCard/DATA/MACHINEDATA.TT.ZIP");
        if (!file.exists()) {
            s = "File is not found!";
            textView.setText(s);
            Log.d("SHENGEL", "File is not found");
            return 1;
        }
        s = "File is found...";
        textView.setText(s);
        Log.d("SHENGEL", "File is found");

        return 0;
    }

    private int copyMachineData() {
        Date date = new Date();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy HH-mm-ss");
        String data = fileSourceName + "/UsbDriveA/" + dateFormat.format(date);
        File folder = new File(data);
        folder.mkdir();
        File copyFile = new File(data + "/" + file.getName());
        try {
            InputStream in = new BufferedInputStream(new FileInputStream(file));
            OutputStream out = new BufferedOutputStream(new FileOutputStream(copyFile));
            byte[] buffer = new byte[1024];
            int lengthRead;
            while ((lengthRead = in.read(buffer)) > 0) {
                out.write(buffer, 0, lengthRead);
                out.flush();
            }
            in.close();
            out.close();
        } catch (IOException e) {
            s = "\r\nCopy is failed!" + "\r\nError: " + e.getMessage();
            textView.append(s);
            return 1;
        }
        s = "\r\nCopy is OK...";
        textView.append(s);
        return 0;
    }

    private void changeMachineData() {
        String passwordAccess = "PasswordAccess\">\r\n<Value>false</Value>";
        String passwordAccessTrue = "PasswordAccess\">\r\n<Value>true</Value>";
        String passwordTrue = "PasswordAccess\">\r\n<Value>true</Value>";
        String machineId = "";
        boolean isFail = false;
        boolean isChanged = false;
        File tempFile = null;
        try {
            // get a temp file
           // tempFile = new File(fileSourceName + "/extSdCard/temp" + (int) (Math.random() * 1000));
            tempFile = new File(fileSourceName + "/UsbDriveA/temp" + (int) (Math.random() * 1000));
            // delete it, otherwise you cannot rename your existing zip to it.
            tempFile.delete();
        } catch (Exception e) {
            s = "\r\nTemp file is not created.\r\nError: " + e.getMessage();
            textView.append(s);
        }

        boolean renameOk = file.renameTo(tempFile);
        if (!renameOk) {
            s = "\r\nCouldn't rename the file " + file.getAbsolutePath() + " to " + tempFile.getAbsolutePath();
            textView.append(s);
            throw new RuntimeException("could not rename the file " + file.getAbsolutePath() + " to " + tempFile.getAbsolutePath());
        }
        try {
            ZipInputStream zin = new ZipInputStream(new FileInputStream(tempFile));
            ZipOutputStream out = new ZipOutputStream(new FileOutputStream(file));
            ZipEntry entry = zin.getNextEntry();
            byte[] buf = new byte[500];
            while (entry != null) {
                /*s = "\r\nget new entry...";
                textView.append(s);*/
                String name = entry.getName();
                if (name.equals("immdata/MachineDisk.xml")) {
                    s = "\r\nFile MachineDisk.xml is found...";
                    textView.append(s);
                    out.putNextEntry(new ZipEntry("immdata/MachineDisk.xml"));
                    int len;
                    while ((len = (zin.read(buf))) > 0) {
                        String sbuf = new String(buf);
                        Log.d("SHENGEL", "BUFFER! " + sbuf);
                        if (sbuf.contains("Machine_ID=\"")) {
                            String tmp = "";
                            Pattern pattern = Pattern.compile("ID=\"\\d*\"");
                            Matcher matcher = pattern.matcher(sbuf);
                            while (matcher.find()) tmp = matcher.group();
                            Pattern p = Pattern.compile("\\d+");
                            Matcher m = p.matcher(tmp);
                            while (m.find()) machineId = m.group();
                            s = "\r\nMachine №" + machineId;
                            textView.append(s);
                            Log.d("SHENGEL", "Machine №" + machineId);

                        }
                        if (sbuf.contains(passwordAccess)) {
                            buf = sbuf.replaceAll(passwordAccess, passwordTrue).getBytes();
                            isChanged = true;
                            s = "\r\nReplace variable was a success...";
                            textView.append(s);
                        }
                        if (sbuf.contains(passwordAccessTrue)) {
                            isChanged = true;
                            s = "\r\nReplace isn't needed";
                            textView.append(s);
                            Log.d("SHENGEL", "Replace isn't needed...");
                        }
                        Log.d("SHENGEL", "" + len);
                        out.write(buf, 0, (len < buf.length) ? len : buf.length);
                        Log.d("SHENGEL", "" + "write buf is OK!");
                    }
                    out.closeEntry();

                } else {
                    // Add ZIP entry to output stream.
                    Log.d("SHENGEL", "buffer is unsuitable!");
                    out.putNextEntry(new ZipEntry(name));
                    // Transfer bytes from the ZIP file to the output file
                    int len;
                    while ((len = zin.read(buf)) > 0) {
                        //out.write(buf, 0, len);
                        out.write(buf, 0, (len < buf.length) ? len : buf.length);
                    }
                    out.closeEntry();
                }
                entry = zin.getNextEntry();
            }
            zin.close();
            out.close();
        } catch (IOException e) {
            isFail = true;
            s = "\r\nConverting data is failed!\r\n" + e.getMessage() + "\r\n" + e.getCause();
            textView.append(s);
            Log.d("SHENGEL", "Converting data is failed!");
        }
        tempFile.delete();
        if (!isFail && isChanged) {
            s = "\r\n\r\nConverting data for machine №" + machineId + " was a success! Congratulations!";
            textView.append(s);
            Log.d("SHENGEL", "Converting data for machine №" + machineId + " was a success! Congratulations!");

        }
        if (!isChanged && !isFail) {
            s = "\r\nProcess was ended without changes!";
            textView.append(s);
            Log.d("SHENGEL", "without changes");
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
