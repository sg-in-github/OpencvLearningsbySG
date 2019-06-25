cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( DisplayImage DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

add_executable(how_to_scan_images how_to_scan_images.cpp)
target_link_libraries(how_to_scan_images ${OpenCV_LIBS} )

add_executable(mat_mask_operations mat_mask_operations.cpp)
target_link_libraries(mat_mask_operations ${OpenCV_LIBS} )
  
add_executable(AdjustBrightnessContrast  AdjustBrightnessContrast.cpp)
target_link_libraries(AdjustBrightnessContrast ${OpenCV_LIBS} )

add_executable(Gdal_imageProcessing Gdal_imageProcessing.cpp)
target_link_libraries(Gdal_imageProcessing ${OpenCV_LIBS} )

add_executable(erosion_dilatation erosion_dilatation.cpp)
target_link_libraries(erosion_dilatation ${OpenCV_LIBS} )
