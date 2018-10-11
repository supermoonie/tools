package com.github.supermoonie;

import com.sun.jna.WString;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        WinProc instance = WinProc.INSTANCE;
        int pid = instance.findProc(new WString("IEDriverServer.exe"));
        instance.terminate(pid);
        System.out.println(pid);
    }
}
