target_precompile_headers(mod
    PRIVATE
        Pch.h
)
target_sources(mod
    PRIVATE
        version.rc
        DllMain.cpp
        Mod.cpp
	    USMTitle.cpp
        TitleMovie.cpp
    PRIVATE FILE_SET HEADERS FILES
        Pch.h
	    USMTitle.h
        TitleMovie.h
        utilities/Helpers.h
        utilities/GameHelpers.h
 )
