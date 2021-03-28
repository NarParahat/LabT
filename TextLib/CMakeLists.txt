file(GLOB hdrs "*.cpp*") #Добавляем в переменную hdrs все файлы с расширением .h
file(GLOB srcs "*.h")#Добавляем в переменную srcs все файлы с расширением .h

add_library(${TextLib} STATIC ${srcs} ${hdrs})

