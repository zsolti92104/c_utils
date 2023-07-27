/**
 * @file file_utils.c
 * @author zspapp (zspapp@mediso.com)
 * @brief File operation utilities.
 * @version 0.1
 * @date 2023-02-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "file_utils.h"


int get_folder_and_file(const char *path, char **folder, char **file)
{
    char * dup_path = strdup(path);

    char* fname = (strrchr(dup_path, '/'));

    if(!strcmp(dup_path, ""))
    {
        //Empty path
        *folder = NULL;
        *file = NULL;
        return FU_ERROR;
    }

    if(!fname) //Path is file
    {
        *folder = NULL;
        *file = strdup(path);
        return FU_PATH_IS_FILE;
    }
    else
    {
        char* fname = (strrchr(dup_path, '/')+1);

        char dir[(fname-dup_path)+1];
        strncpy(dir, dup_path, fname-dup_path);
        dir[fname-dup_path] = '\0';
        *folder = strdup(dir);
        *file = strdup(fname);
    }
    return FU_PATH_COMPLETE;
}


int check_file_and_create(const char *path, bool create_flag)
{
    char *folder;
    char *file;
    struct stat st = {0};

    if(get_folder_and_file(path, &folder, &file) == FU_ERROR)
    {
        //Path empty
        return FU_ERROR;
    }

    //Check and create folder if not exists
    if(folder != NULL)
    {
        //Check if folder exists
        if ((stat(folder, &st) == -1) && create_flag) 
        {
            mkdir(folder, 0700); //Create folder with owner RWX access
        }
    }

    if (access(path, F_OK) == 0) 
    {
        //File exists!
        return FU_FILE_EXISTS;
    }
    else if(create_flag)
    {
        //Create file
        int fd = open(path,  O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

        if(fd > 0)
        {
            //File created!
            close(fd);
            return FU_FILE_CREATED;
        }
        else
        {
            //Can't create file!
            return FU_ERROR;
        }
    }

    return FU_FILE_DOES_NOT_EXISTS;
}

int write_calib_table(const char *file, float calib_table[][3], int rows)
{
    FILE* fp = fopen(file, "w");

	if (!fp)
    {
		//Error in file opening: Can't open file to write
		return FU_ERROR;
	}

	//Saving data to file
    size_t i;
    for (i = 0; i < rows-1; i++)
    {
        fprintf(fp, "%f; %f; %f\n", calib_table[i][0], calib_table[i][1], calib_table[i][2]);
    }
    fprintf(fp, "%f; %f; %f", calib_table[i][0], calib_table[i][1], calib_table[i][2]);

	fclose(fp);

    return FU_WRITE_SUCCESS;
}

int read_calib_table(const char *file, float calib_table[][3], int rows)
{
    FILE* fp = fopen(file, "r");
 
    if (!fp)
    {
        //Can't open file to read
        return FU_ERROR;       
    }
    else 
    {
        char buffer[256];
        const char delim[2] = ";";
 
        int row = 0;
        int column = 0;

        while (fgets(buffer, 256, fp))
        {
            column = 0;
 
            // Splitting the data
            char * dupped_line = strdup(buffer);
            char* value = strtok(buffer, delim);
 
            while (value)
            {
                calib_table[row][column] = atof(value);
                value = strtok(NULL, delim);
                column++;
            }

            if(row == rows)
            {
                fclose(fp);
                return FU_READ_SUCCESS;
            }

            row++;
        }
    }

    // Close the file
    fclose(fp);
    return FU_READ_SUCCESS;
}