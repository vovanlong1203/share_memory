#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#define BUF_SIZE 1024

void write_process(HANDLE hMapFile, LPCTSTR pBuf, TCHAR szName[], TCHAR szMsg[]) {
    CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
}

void read_process(HANDLE hMapFile, LPCTSTR pBuf, TCHAR szName[]) {
    MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
}

int _tmain()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;
    while (true) {
        TCHAR szName[] = TEXT("Global\MyFileMappingObject");
        TCHAR szMsg[45];
        _fgetts(szMsg, sizeof(szMsg), stdin);

        hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,          // read/write access
            0,                       // maximum object size (high-order DWORD)
            BUF_SIZE,                // maximum object size (low-order DWORD)
            szName);                 // name of mapping object
        pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            BUF_SIZE);
        write_process(hMapFile, pBuf, szName, szMsg);
        _getch();
        hMapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,   // read/write access
            FALSE,                 // do not inherit the name
            szName);               // name of mapping object
        read_process(hMapFile, pBuf, szName);
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);

    }
    return 0;
}