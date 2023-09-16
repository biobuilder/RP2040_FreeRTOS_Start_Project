
# set source files for this particular application
set(  SOURCE_FILES 
      main.c
      application.c
      #../somelibrary/somefile.c
      )

# add executable file
add_executable( ${PROJECT_NAME}     ${SOURCE_FILES} )

# link libraries
target_link_libraries(  ${PROJECT_NAME}         # links libraries to this particular target executable
                        pico_stdlib             # pico sdk
                        FreeRTOS-Kernel-Heap3   # which heap to use
                        #FREERTOS_PORT
                        )

# create map/bin/hex/uf2 files
pico_add_extra_outputs( ${PROJECT_NAME} )

# include other folder directories
target_include_directories( ${PROJECT_NAME}
                            PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                            #PRIVATE ../somelibrary/somesubfolder
                            )