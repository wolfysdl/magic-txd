/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.2
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        FileSystem/src/fsinternal/CFileSystem.internal.h
*  PURPOSE:     Master header of the internal FileSystem modules
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef _FILESYSTEM_INTERNAL_LOGIC_
#define _FILESYSTEM_INTERNAL_LOGIC_

// Generic file access stuff.
enum class eFileMode
{
    UNKNOWN,
    CREATE,
    OPEN
};

#define FILE_ACCESS_WRITE   0x01
#define FILE_ACCESS_READ    0x02

#ifndef _WIN32
#define MAX_PATH 260
#else
#include <direct.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <dirent.h>
#endif //__linux__

// FileSystem is plugin-based. Drivers register a plugin memory to build on.
#include <MemoryUtils.h>

// The native class of the FileSystem library.
struct CFileSystemNative : public CFileSystem
{
public:
    inline CFileSystemNative( const fs_construction_params& params ) : CFileSystem( params )
    {
        return;
    }

    inline ~CFileSystemNative( void )
    {
        return;
    }

    // All drivers have to add their registration routines here.
    static void RegisterZIPDriver( const fs_construction_params& params );
    static void UnregisterZIPDriver( void );

    static void RegisterIMGDriver( const fs_construction_params& params );
    static void UnregisterIMGDriver( void );

    // Generic things.
    template <typename charType>
    bool                GenGetSystemRootDescriptor( const charType *path, filePath& descOut ) const;
    template <typename charType>
    CFileTranslator*    GenCreateTranslator( const charType *path, eDirOpenFlags flags );
    template <typename charType>
    CFileTranslator*    GenCreateSystemMinimumAccessPoint( const charType *path, eDirOpenFlags flags = DIR_FLAG_NONE );
};

typedef StaticPluginClassFactory <CFileSystemNative> fileSystemFactory_t;

extern fileSystemFactory_t _fileSysFactory;

#include "CFileSystem.internal.common.h"
#include "CFileSystem.internal.lockutil.h"
#include "CFileSystem.random.h"
#include "CFileSystem.stream.buffered.h"
#include "CFileSystem.translator.pathutil.h"
#include "CFileSystem.translator.widewrap.h"
#include "CFileSystem.internal.repo.h"
#include "CFileSystem.config.h"
#include "CFileSystem.FileDataPresence.h"

#endif //_FILESYSTEM_INTERNAL_LOGIC_