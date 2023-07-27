/**
 * @file file_utils.h
 * @author zspapp (zspapp@mediso.com)
 * @brief File operation utilities.
 * @version 0.1
 * @date 2023-02-10
 * 
 * @copyright Copyright (c) 2023
 * 
 * @note Return values are defined in "file_util_ret_en" enum.
 * Return 0 at every function means error. Ret value >0 is ok.
 */
#include "std_includes.h"

enum file_util_ret_en
{
    FU_ERROR = 0,
    FU_PATH_IS_FILE, //Path is just a file name
    FU_PATH_COMPLETE, //Path contains file and folder
    FU_FILE_EXISTS,
    FU_FILE_DOES_NOT_EXISTS,
    FU_FILE_CREATED,
    FU_WRITE_SUCCESS,
    FU_READ_SUCCESS
};

/**
 * @brief Get the folder and file object
 * 
 * @param path 
 * @param folder 
 * @param file 
 * @return int 
 */
int get_folder_and_file(const char *path, char **folder, char **file);


/**
 * @brief 
 * 
 * @param path 
 * @return int 
 */
int check_file_and_create(const char *path, bool create_flag);

/**
 * @brief 
 * 
 * @param file 
 * @param calib_table 
 * @param rows 
 * @return int 
 */
int write_calib_table(const char *file, float calib_table[][3], int rows);

/**
 * @brief 
 * 
 * @param file 
 * @param calib_table 
 * @param rows 
 * @return int 
 */
int read_calib_table(const char *file, float calib_table[][3], int rows);