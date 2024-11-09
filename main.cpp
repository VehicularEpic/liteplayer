#ifdef WIN32
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    return 0;
}
#else
int main(int argc, char const *argv[]) {
    return 0;
}
#endif
