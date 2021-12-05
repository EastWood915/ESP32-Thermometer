idf_component_register(SRCS "dweet.c"
                       INCLUDE_DIRS "." "$ENV{IDF_PATH}/components"
                       REQUIRES esp-tls)