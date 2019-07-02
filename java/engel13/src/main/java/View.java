package main.java;

import javax.swing.*;
import javax.swing.event.MenuEvent;
import javax.swing.event.MenuListener;
import javax.swing.filechooser.FileFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class View extends JFrame implements ActionListener {
    private JPanel jPanel = new JPanel();

    public JPanel getjPanel() {
        return jPanel;
    }

    private Controller controller;
    private JLabel jLabelIn = new JLabel();
    private JLabel jLabelOut = new JLabel();
    private JCheckBox jCheckBox;
    private ButtonGroup buttonGroup = new ButtonGroup();

    public void setController(Controller controller) {
        this.controller = controller;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String text = e.getActionCommand();
        if (text.equals("Выход")) controller.exit();
        else if (text.equals("О программе \"Engel13\"")) System.out.println("about");
        else if (text.equals("Инструкция по работе с программой")) System.out.println("13");
        else if (text.equals("Выбор исходной машиндаты")) {
            controller.loadMachineData();
        }
        else if (text.equals("Выходной файл")) {
            System.out.println("Выходной файл");
            createLabelButtonOutput("c://dataNewgvetgvetgvetgvetgbvtehbtegbvtgbvtgbvgvetg.txt");
        }



        jPanel.revalidate();
    }

    public void init(){
        createWindow();
        createMenu();
        createButtonLoad();
        createLabelButtonLoad("");
        createCheckBox();
        createButtonOutput();
        createLabelButtonOutput("");
        createJRadioButtonPassword();
        createJRadioButtonCard();
        createButtonStart();
        revalidate();
    }

    private void createButtonLoad(){
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.weightx = 0;
        constraints.weighty = 0.1;
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets = new Insets(10, 0,0,0);

        JButton buttonLoad = new JButton("Выбор исходной машиндаты");
        jPanel.add(buttonLoad, constraints);
        buttonLoad.addActionListener(this);
        revalidate();
    }

    protected void createLabelButtonLoad(String text){
        GridBagConstraints constraints = new GridBagConstraints();
//        constraints.weightx = 0;
//        constraints.weighty = 0;
        constraints.gridx = 0;
        constraints.gridy = 1;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.insets = new Insets(10, 0,0,0);

        constraints.anchor = GridBagConstraints.WEST;
        jLabelIn.setText("Выбранный путь:" + text);
        jPanel.add(jLabelIn, constraints);
        revalidate();
    }

    private void createCheckBox(){
        GridBagConstraints constraints = new GridBagConstraints();
//        constraints.weightx = 0;
//        constraints.weighty = 0;
        constraints.gridx = 0;
        constraints.gridy = 3;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.insets = new Insets(30, 0,0,0);


        jCheckBox = new JCheckBox("Внести изменения в выбранный файл");
        jPanel.add(jCheckBox, constraints);
    }

    private void createButtonOutput(){
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.weightx = 0;
        constraints.weighty = 0.1;
        constraints.gridx = 0;
        constraints.gridy = 4;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets = new Insets(10, 0,0,0);

        JButton buttonOutput = new JButton("Выходной файл");
        buttonOutput.addActionListener(this);
        jPanel.add(buttonOutput, constraints);
        revalidate();

    }

    private void createLabelButtonOutput(String text){
        GridBagConstraints constraints = new GridBagConstraints();
//        constraints.weightx = 0;
//        constraints.weighty = 2;
        constraints.gridx = 0;
        constraints.gridy = 5;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.anchor = GridBagConstraints.WEST;
        constraints.insets = new Insets(10, 0,0,0);

        jLabelOut.setText("Выбранный путь:" + text);
        jPanel.add(jLabelOut, constraints);
        revalidate();
    }

    private void createJRadioButtonPassword(){
        GridBagConstraints constraints = new GridBagConstraints();
//        constraints.weightx = 0;
//        constraints.weighty = 0;
        constraints.gridx = 0;
        constraints.gridy = 7;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.insets = new Insets(20, 0,0,0);
        constraints.anchor = GridBagConstraints.WEST;

        JRadioButton jRadioButton = new JRadioButton("Разрешить доступ по паролю");
        jRadioButton.setSelected(true);
        buttonGroup.add(jRadioButton);
        jPanel.add(jRadioButton, constraints);
    }

    private void createJRadioButtonCard(){
        GridBagConstraints constraints = new GridBagConstraints();
//        constraints.weightx = 0;
//        constraints.weighty = 0;
        constraints.gridx = 0;
        constraints.gridy = 8;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.anchor = GridBagConstraints.WEST;

        JRadioButton jRadioButton = new JRadioButton("Доступ только по карте");
        buttonGroup.add(jRadioButton);
        jPanel.add(jRadioButton, constraints);
    }

    private void createButtonStart(){
        GridBagConstraints constraints = new GridBagConstraints();
        constraints.weightx = 0;
        constraints.weighty = 0.2;
        constraints.gridx = 0;
        constraints.gridy = 9;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets = new Insets(30, 0,0,0);

        JButton start = new JButton("СТАРТ");
        start.addActionListener(this);
        jPanel.add(start, constraints);
        revalidate();

    }


    private void createMenu(){
        JMenuBar jMenuBar = new JMenuBar();
        JMenu info = new JMenu("Cправка");
        info.setMnemonic('C');
        jMenuBar.add(info);

        JMenuItem instruction = new JMenuItem("Инструкция по работе с программой", 'И');
        JMenuItem about = new JMenuItem("О программе \"Engel13\"", 'О');
        JMenuItem exit = new JMenuItem("Выход", 'В');

        info.add(instruction);
        info.add(about);
        info.addSeparator();
        info.add(exit);

        instruction.addActionListener(this);
        about.addActionListener(this);
        exit.addActionListener(this);

        setJMenuBar(jMenuBar);

    }

    private void createWindow(){
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        setBounds(dimension.width/2-250, dimension.height/2 - 250, 700, 500);
        setTitle("Программа для изменения типа доступа для ТПА Engel");
        this.add(jPanel);
    }

    public View() {
        GridBagLayout gridBagLayout = new GridBagLayout();
        jPanel.setLayout(gridBagLayout);
    }



}