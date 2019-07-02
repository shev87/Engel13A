package main.java;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import java.io.File;

public class Controller {
    private View view;
    private File fileOriginal;

    public static void main(String[] args) {
        View view = new View();
        Controller controller = new Controller(view);
        view.setController(controller);
        view.init();
        controller.init();
    }

    public void exit(){
        System.exit(0);
    }

    public void init(){

    }

    public void loadMachineData(){
        System.out.println("Выбор исходной машиндаты");
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("c://"));
        //fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        fileChooser.setFileFilter(new FileFilter() {
            @Override
            public boolean accept(File f) {
                if (f.getName().toLowerCase().endsWith(".zip")) return true;
                if (f.isDirectory()) return true;
                return false;
            }

            @Override
            public String getDescription() {
                return "ZIP";
            }
        });
        fileChooser.showOpenDialog(view.getjPanel());
        try {
            fileOriginal = fileChooser.getSelectedFile();
            view.createLabelButtonLoad(fileOriginal.getAbsolutePath());
        } catch (NullPointerException e) {}
    }

    public Controller(View view) {
        this.view = view;
    }
}
