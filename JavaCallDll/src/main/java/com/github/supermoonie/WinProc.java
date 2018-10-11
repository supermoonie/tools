package com.github.supermoonie;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.WString;
import com.sun.jna.win32.W32APIOptions;

/**
 * @author supermoonie
 * @date 2018/10/11 16:26
 */
public interface WinProc extends Library {

    WinProc INSTANCE = Native.loadLibrary("WinProc", WinProc.class, W32APIOptions.DEFAULT_OPTIONS);

    /**
     * ...
     *
     * @param procName
     * @return
     */
    int findProc(WString procName);

    void terminate(int pid);
}
