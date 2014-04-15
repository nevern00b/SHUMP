--Application name
local name = "SHUMP"

--Directory structure
local project_location =    os.getcwd()      .. "/../"
local build_location =      project_location .. "build/"
local data_location =       project_location .. "data/"
local externals_location =  project_location .. "external/"
local source_location =     project_location .. "src/"
--local freetype_gl =         externals_location .. "freetype-gl/include/"
local gl3w =                externals_location .. "gl3w/src/"
local preprocessor_vars =   {"_CRT_SECURE_NO_WARNINGS", "GLM_FORCE_RADIANS"}
local additional_libs =     {"opengl32"}

--Find out which libs have bins and includes
local lib_dirs_bin = {}
local lib_dirs_include = {}
local lib_dirs = os.matchdirs(externals_location .. "*");
for i,lib_dir in pairs(lib_dirs) do
    lib_dirs_include[i] = lib_dir .. "/include/" 
    local lib_dir_bin = lib_dir .. "/lib/"
    if os.isdir(string.gsub(lib_dir_bin, "/$", "")) then
        lib_dirs_bin[i] = lib_dir_bin 
    end
end

--Adds libs to the project
function addlibs(system, architecture, build_type)
    local endpath = system .. "/" .. architecture .. "/" .. build_type .. "/"
    for i,lib_dir in pairs(lib_dirs_bin) do
        local full_path = lib_dir .. endpath
        libdirs (full_path)
        local lib_paths = os.matchfiles(full_path .. "*")
        for j,lib_path in pairs(lib_paths) do
            local lib_name = path.getbasename(lib_path)
            local lib_extension = path.getextension(lib_path)
            if os.get() == "windows" then
                if lib_extension == ".lib" then 
                    links (lib_name)
                elseif lib_extension == ".dll" then
                    os.copyfile(lib_path, project_location .. lib_name .. lib_extension)
                end
            end
        end
    end
end

--Delete the old build and run folders
os.rmdir(string.gsub(build_location, "/$", ""))
os.mkdir(build_location)

--Set up the project
solution ( name )
    location ( build_location )
project ( name )
    kind ("ConsoleApp")
    language ("C++")
    defines ( preprocessor_vars )                   	--preprocessor hints/ variables
    links ( additional_libs )							--include random libs from the OS
    table.insert(lib_dirs_include, source_location)		--add source folder to the includes
    includedirs ( lib_dirs_include )					--include header files from external libraries
    files { source_location  .. "**" }              	--include all of our source code
    --files { freetype_gl .. "**" }                   	--freetype-gl has some .cpp files that need to be added
    files { gl3w .. "**" }                          	--gl3w has a .c file that needs to be added
    files { data_location    .. "**" }              	--include all of the data files
    location ( build_location )                     	--this is where the project is built
    targetdir ( build_location )                    	--this is where the exe gets built
    debugdir ( project_location )                   	--this is where the debug exe gets built

    --Create debug and release modes
    local platform = _OPTIONS["platform"]
    configurations { "Debug", "Release" }
    configuration { "Debug" }
        flags   { "Symbols" }
        defines { "DEBUG" }
        addlibs(os.get(), platform, "Debug")
    configuration { "Release" }
        flags   { "OptimizeSpeed" }
        defines { "NDEBUG" }
        addlibs(os.get(), platform, "Release")