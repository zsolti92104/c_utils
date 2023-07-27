#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#define UT_UTILS_MAX_PATH_SIZE      4096
#define UT_UTILS_EXEC_FOLDERS_NUM   (sizeof(ut_utils_exec_folders_apc) / sizeof(ut_utils_exec_folders_apc[0]))

const char* ut_utils_exec_folders_apc[] = { "Debug", "Release", "TestCoverage"};
char ut_utils_build_cfg_dirname_ac[UT_UTILS_MAX_PATH_SIZE];

void ut_utils_chdir_cdt_unittest(void)
{
    char cwd_ac[UT_UTILS_MAX_PATH_SIZE];

    char* cwd_pc = getcwd(cwd_ac, sizeof(cwd_ac));

    if(cwd_pc)
    {
        char* substr_loc_pc = strstr(cwd_pc, PATH_SEPARATOR "cdt_unittest");


        if(substr_loc_pc)
        {
            char subpath_ac[UT_UTILS_MAX_PATH_SIZE];
            uint16_t idx_u16;

            for(idx_u16 = 0; idx_u16 < UT_UTILS_EXEC_FOLDERS_NUM; idx_u16++)
            {
                strcpy(subpath_ac, "cdt_unittest");
                strcat(subpath_ac, PATH_SEPARATOR);
                strcat(subpath_ac, ut_utils_exec_folders_apc[idx_u16]);

                substr_loc_pc = strstr(cwd_pc, subpath_ac);
                if(substr_loc_pc)
                {
                    break;
                }
            }

            if(idx_u16 != UT_UTILS_EXEC_FOLDERS_NUM)
            {
                chdir("..");
                strcpy(ut_utils_build_cfg_dirname_ac, ut_utils_exec_folders_apc[idx_u16]);
            }
        }
    }
}


void ut_utils_restore_cwd(void)
{
    if(ut_utils_build_cfg_dirname_ac[0] != '\0')
    {
        chdir(ut_utils_build_cfg_dirname_ac);
        ut_utils_build_cfg_dirname_ac[0] = '\0';
    }
}


void ut_utils_print_cwd(void)
{
    char cwd_ac[UT_UTILS_MAX_PATH_SIZE];

    char* cwd_pc = getcwd(cwd_ac, sizeof(cwd_ac));

    if(cwd_pc)
    {
        printf("ut_utils - current working directory: %s\n", cwd_pc);
    }
}

