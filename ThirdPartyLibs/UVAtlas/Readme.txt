-----------------------------------
UVAtlas - isochart texture atlasing
-----------------------------------

Copyright (c) Microsoft Corporation. All rights reserved.

June 18, 2015

This package contains UVAtlas, a shared source library for creating and packing an
isochart texture atlas.

The source is written for Visual Studio 2010, 2012, 2013, or 2015. It is recommended that you
make use of the Windows 8.1 SDK and Windows 7 Service Pack 1 or later.

Details on using the Windows 8.1 SDK with VS 2010 are described on the Visual C++ Team Blog:
<http://blogs.msdn.com/b/vcblog/archive/2012/11/23/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects.aspx>

These components are designed to work without requiring any content from the DirectX SDK. For details,
see "Where is the DirectX SDK?" <http://msdn.microsoft.com/en-us/library/ee663275.aspx>.

Inc\
    Public Header File (in the DirectX C++ namespace):

    UVtlas.h
    - UVAtlasCreate
    - UVAtlasPartition
    - UVAtlasPack
    - UVAtlasComputeIMTFromPerVertexSignal
    - UVAtlasComputeIMTFromSignal
    - UVAtlasComputeIMTFromTexture
    - UVAtlasComputeIMTFromPerTexelSignal
    - UVAtlasApplyRemap

geodesics\
isochart\
    Library source files

UVAtasTool\
    Command line tool and sample for UVAtlas library

    To build this tool, you need the DirectXTex (http://go.microsoft.com/fwlink/?LinkId=248926)
    and DirectXMesh (http://go.microsoft.com/fwlink/?LinkID=324981) libraries in the following
    directory structure:
        .\DirectXTex\DirectXTex
        .\DirectXMesh\DirectXMesh
        .\DirectXMesh\Utilities
        .\UVAtlas\UVAtlas
        .\UVAtlas\UVAtlasTool

All content and source code for this package are subject to the terms of the MIT License.
<http://opensource.org/licenses/MIT>.

Documentation is available at <https://github.com/Microsoft/UVAtlas/wiki>.

For the latest version of UVAtlas, bug reports, etc. please visit the project site.

http://go.microsoft.com/fwlink/?LinkID=512686

Further reading:

    Zhou et al, "Iso-charts: Stretch-driven Mesh Parameterization using Spectral Analysis",
    Eurographics Symposium on Geometry Processing (2004)
    http://research.microsoft.com/en-us/um/people/johnsny/papers/isochart.pdf

    Sander et al. "Signal-Specialized Parametrization" Europgraphics 2002
    http://research.microsoft.com/en-us/um/people/johnsny/papers/ssp.pdf


---------------
RELEASE HISTORY
---------------

June 18, 2015
    Fixed bugs with handling of E_ABORT from user callback
    Added ESC to abort to uvatlas sample

April 9, 2015
    Added projects for Windows apps Technical Preview
    Fixes for potential divide-by-zero cases
    Fix for memory allocation problem
    Added error detection for invalid partitioning
    uvatlas: fix when importing from .vbo
    Minor code cleanup

November 12, 2014
    Original release
