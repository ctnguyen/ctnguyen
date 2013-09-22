## src folder might have many folder
## in this exemple, there are only one
## but it would be good to use a loop for adding the sub folder

foreach(DIR
	modules
)
	add_subdirectory(${DIR})
endforeach()
