package com.github.supermoonie;

import javax.swing.*;
import java.io.*;

/**
 * Hello world!
 *
 * @author Administrator
 */
public class App 
{
    static {
        System.setProperty("java.awt.headless", "false");
    }

    public static void main( String[] args ) throws IOException, InterruptedException {
        ProcessBuilder processBuilder = new ProcessBuilder("C:\\C++\\tools\\ProcessCommunication\\Debug\\ProcessCommunication.exe");
        Process process = processBuilder.start();
        InputStream inputStream = process.getInputStream();
        OutputStream outputStream = process.getOutputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println("receive: " + line);
            String input = JOptionPane.showInputDialog("input");
            System.out.println("send: " + input);
            writer.write(input);
            writer.newLine();
            writer.flush();
        }
        process.waitFor();
        int code = process.exitValue();
        System.out.println("exit value: " + code);
    }
}
