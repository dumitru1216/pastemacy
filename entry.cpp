#include "includes.h"

int __stdcall DllMain( HMODULE self, ulong_t reason, void *reserved ) {
    if( reason == DLL_PROCESS_ATTACH ) {
        AllocConsole( );
        freopen_s( ( FILE** )stdin, XOR( "CONIN$" ), XOR( "r" ), stdin );
        freopen_s( ( FILE** )stdout, XOR( "CONOUT$" ), XOR( "w" ), stdout );
        SetConsoleTitleA( "hyperbius | debugger" );

        // we dont need bunch of shit
        Client::init( nullptr );
        return 1;
    }

    return 0;
}