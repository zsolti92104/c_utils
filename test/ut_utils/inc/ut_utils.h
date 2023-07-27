#ifndef UT_UTILS_H_
#define UT_UTILS_H_

#define UT_UTILS_RESOURCE_PATH              "..\\..\\test\\resource"
#define UT_UTILS_GEN_RESOURCE_PATH(PATH)    UT_UTILS_RESOURCE_PATH "\\" PATH

void ut_utils_chdir_cdt_unittest(void);
void ut_utils_restore_cwd(void);
void ut_utils_print_cwd(void);

#endif /* UT_UTILS_H_ */
