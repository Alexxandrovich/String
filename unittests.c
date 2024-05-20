#include "unittests.h"

START_TEST(s21_memchr_test) {
  ck_assert_ptr_eq(s21_memchr("", '\0', 0), memchr("", '\0', 0));
  ck_assert_ptr_eq(s21_memchr("Example", '\0', 5), memchr("Example", '\0', 5));
  ck_assert_ptr_eq(s21_memchr("Example", 'E', 8), memchr("Example", 'E', 8));
  ck_assert_ptr_eq(s21_memchr("Example", 'e', 8), memchr("Example", 'e', 8));
  ck_assert_ptr_eq(s21_memchr("Example", 'm', 8), memchr("Example", 'm', 8));
}
END_TEST

START_TEST(s21_strchr_test) {
  ck_assert_pstr_eq(s21_strchr("Example", 'E'), strchr("Example", 'E'));
  ck_assert_pstr_eq(s21_strchr("Example", 'a'), strchr("Example", 'a'));
  ck_assert_pstr_eq(s21_strchr("Example", 'e'), strchr("Example", 'e'));
  ck_assert_pstr_eq(s21_strchr("Example", '3'), strchr("Example", '3'));
  ck_assert_pstr_eq(s21_strchr("Example", 'A'), strchr("Example", 'A'));
}
END_TEST

START_TEST(s21_strrchr_test) {
  ck_assert_pstr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
  ck_assert_pstr_eq(s21_strrchr("Example", '\0'), strrchr("Example", '\0'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'a'), strrchr("Example", 'a'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'k'), strrchr("Example", 'k'));
  ck_assert_pstr_eq(s21_strrchr("Example", 'E'), strrchr("Example", 'E'));
}
END_TEST

START_TEST(s21_strpbrk_test) {
  ck_assert_pstr_eq(s21_strpbrk("", ""), strpbrk("", ""));
  ck_assert_pstr_eq(s21_strpbrk("Example", ""), strpbrk("Example", ""));
  ck_assert_pstr_eq(s21_strpbrk("", "Example"), strpbrk("", "Example"));
  ck_assert_pstr_eq(s21_strpbrk("Example", "a"), strpbrk("Example", "a"));
  ck_assert_pstr_eq(s21_strpbrk("Example", "\0"), strpbrk("Example", "\0"));
}
END_TEST

START_TEST(s21_strstr_tets) {
  ck_assert_pstr_eq(s21_strstr("", ""), strstr("", ""));
  ck_assert_pstr_eq(s21_strstr("", "Example"), strstr("", "Example"));
  ck_assert_pstr_eq(s21_strstr("Example", ""), strstr("Example", ""));
  ck_assert_pstr_eq(s21_strstr("Example", "le"), strstr("Example", "le"));
  ck_assert_pstr_eq(s21_strstr("Example", "kj"), strstr("Example", "kj"));
}
END_TEST

START_TEST(s21_strerror_test) {
  for (int i = -1; i < 135; i++) {
    char *err1 = s21_strerror(i);
    char *err2 = strerror(i);
    ck_assert_str_eq(err1, err2);
  }
}
END_TEST

START_TEST(s21_strncat_test) {
  char dest1[32], src1[32];
  strcpy(dest1, "");
  strcpy(src1, "");
  ck_assert_str_eq(s21_strncat(dest1, src1, 0), strncat(dest1, src1, 0));

  char dest2[32], src2[32];
  strcpy(dest2, "Example");
  strcpy(src2, "");
  ck_assert_str_eq(s21_strncat(dest2, src2, 0), strncat(dest2, src2, 0));

  char dest3[32], src3[32];
  strcpy(dest3, "");
  strcpy(src3, "bla");
  ck_assert_str_eq(s21_strncat(dest3, src3, 0), strncat(dest3, src3, 0));

  char dest4[32], src4[32];
  strcpy(dest4, "Example");
  strcpy(src4, "bla");
  ck_assert_str_eq(s21_strncat(dest4, src4, 2), strncat(dest4, src4, 2));

  char dest5[32], src5[32];
  strcpy(dest5, "Example");
  strcpy(src5, "bla");
  ck_assert_str_eq(s21_strncat(dest5, src5, 8), strncat(dest5, src5, 8));

  char dest6[32], src6[32];
  strcpy(dest6, "");
  strcpy(src6, "bla");
  ck_assert_str_eq(s21_strncat(dest6, src6, 8), strncat(dest6, src6, 8));
}
END_TEST

START_TEST(s21_strtok_test) {
  char str1[] = "Blabla.ba++F.oora_! tyigdyik==Sh.osa";
  char str2[] = "Blabla.ba++F.oora_! tyigdyik==Sh.osa";
  const char delims[] = ".";

  char *got = s21_strtok(str1, delims);
  char *expected = strtok(str2, delims);

  ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));
  ck_assert_str_eq(got, expected);

  while (got && expected) {
    got = s21_strtok(S21_NULL, delims);
    expected = strtok(S21_NULL, delims);

    ck_assert_uint_eq(s21_strlen(got), s21_strlen(expected));

    if (got || expected) {
      ck_assert_str_eq(got, expected);
    } else {
      ck_assert_ptr_null(got);
      ck_assert_ptr_null(expected);
    }
  }
}
END_TEST

START_TEST(test_s_21_sscanf_d0) {
  char str[] = "";
  char format[] = "";
  int s21_a, a, s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
}
END_TEST

START_TEST(test_s_21_sscanf_d1) {
  char str[] = "125 99";
  char format[] = "%d %d";
  int s21_a, a, s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_d2) {
  char str[] = "125";
  char format[] = "%d";
  int s21_a, a;
  ck_assert(s21_sscanf(str, format, &s21_a) == sscanf(str, format, &a));
  ck_assert_int_eq(s21_a, a);
}
END_TEST

START_TEST(test_s_21_sscanf_d3) {
  char str[] = "125 0.33";
  char format[] = "%d %d";
  int s21_a, a, s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_d4) {
  char str[] = "123456 3";
  char format[] = "%*2d %d %d";
  int s21_a, s21_b;
  int a, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_d5) {
  char str[] = "1234";
  char format[] = "%*2d %100d";
  int s21_a, a, s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
}
END_TEST

START_TEST(test_s_21_sscanf_d6) {
  char str[] = "\n\t\r\v123456\n\f3";
  char format[] = "%*2d %d %d";
  int s21_a, s21_b;
  int a, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_d7) {
  char str[] = "1234563";
  char format[] = "%1d %2d %3d";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_d8) {
  char str[] = "1234563";
  char format[] = "%*4d %1d %1d %1d";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_d9) {
  char str[] = "1234563";
  char format[] = "%1hd %1ld";
  short s21_a, a;
  long s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));

  ck_assert(s21_a == a);
  ck_assert(s21_b == b);
}
END_TEST

START_TEST(test_s_21_sscanf_d10) {
  char str[] = "1234563";
  char format[] = "%*1hd %*1ld %*1Ld";
  short s21_a, a;
  long s21_b, b;
  long long s21_c, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
}
END_TEST

START_TEST(test_s_21_sscanf_d11) {
  char str[] = "-123 0456 +789";
  char format[] = "%d %d %d";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_o1) {
  char str[] = "1";
  char format[] = "%d";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
}
END_TEST

START_TEST(test_s_21_sscanf_o2) {
  char str[] = "0000";
  char format[] = "%o";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
}
END_TEST

START_TEST(test_s_21_sscanf_o3) {
  char str[] = "0x11 78";
  char format[] = "%o %o";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
}
END_TEST

START_TEST(test_s_21_sscanf_o4) {
  char str[] = "10020000777";
  char format[] = "%3o %3o %o";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_c5) {
  char str[] = "-1234563";
  char format[] = "%2ho %1lo";
  short s21_a, a;
  long s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_x1) {
  char str[] = "A b C";
  char format[] = "%x %x %X";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_x2) {
  char str[] = "0xAA 0Xbbb -CFFFFFF";
  char format[] = "%x %x %3X";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_x3) {
  char str[] = "-AAAA -0xBBBB -CcCc";
  char format[] = "%hx %100lX";
  short s21_a, a;
  long s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_x4) {
  char str[] = "-AAAAA 0x11000000000";
  char format[] = "%hx %100lX";
  short s21_a, a;
  long s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_x5) {
  char str[] = "fFFFF fFFFFFFFFFFFFFFFF fFFFFFFFFFFFFFFFF";
  char format[] = "%hx %lX";
  short s21_a, a;
  long s21_b, b;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b) ==
            sscanf(str, format, &a, &b));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
}
END_TEST

START_TEST(test_s_21_sscanf_i1) {
  char str[] = "0xAA 088";
  char format[] = "%i %i %i";
  int s21_a, s21_b, s21_c;
  int a, b, c;
  ck_assert(s21_sscanf(str, format, &s21_a, &s21_b, &s21_c) ==
            sscanf(str, format, &a, &b, &c));
  ck_assert_int_eq(s21_a, a);
  ck_assert_int_eq(s21_b, b);
  ck_assert_int_eq(s21_c, c);
}
END_TEST

START_TEST(test_s_21_sscanf_f1) {
  char str[] = "0.000001 -8879.12345678992";
  char format[] = "%f %Lf";
  float f1, f2;
  long double ld1, ld2;
  ck_assert(s21_sscanf(str, format, &f1, &ld1) ==
            sscanf(str, format, &f2, &ld2));
  ck_assert_float_eq(f1, f2);
  ck_assert_ldouble_eq(ld1, ld2);
}
END_TEST

START_TEST(test_s_21_sscanf_f2) {
  char str[] = "0.000001 12.1234567899 -8879.12345678992";
  char format[] = "%f %5lf %*d %7Lf";
  float f1, f2;
  double d1, d2;
  long double ld1, ld2;
  ck_assert(s21_sscanf(str, format, &f1, &d1, &ld1) ==
            sscanf(str, format, &f2, &d2, &ld2));
  ck_assert_float_eq(f1, f2);
  ck_assert_double_eq(d1, d2);
  ck_assert_ldouble_eq(ld1, ld2);
}
END_TEST

START_TEST(test_s_21_sscanf_s1) {
  char str[] = "0.000001 12.1234567899 -8879.12345678992";
  char format[] = "%s %s %s";
  char ans1[100], ans2[100], ans3[100];
  char ans4[100], ans5[100], ans6[100];
  ck_assert(s21_sscanf(str, format, ans1, ans2, ans3) ==
            sscanf(str, format, ans4, ans5, ans6));
  ck_assert_str_eq(ans1, ans4);
  ck_assert_str_eq(ans2, ans5);
  ck_assert_str_eq(ans3, ans6);
}
END_TEST

START_TEST(test_s_21_sscanf_s2) {
  char str[] = "  0.000001\n\n12.1234567899\t\t-8879.12345678992\v";
  char format[] = "%s %s %s";
  char ans1[100], ans2[100], ans3[100];
  char ans4[100], ans5[100], ans6[100];
  ck_assert(s21_sscanf(str, format, ans1, ans2, ans3) ==
            sscanf(str, format, ans4, ans5, ans6));
  ck_assert_str_eq(ans1, ans4);
  ck_assert_str_eq(ans2, ans5);
  ck_assert_str_eq(ans3, ans6);
}
END_TEST

START_TEST(test_s_21_sscanf_s3) {
  char str[] = "0.000001 12.1234567899 -8879.12345678992";
  char format[] = "%3s %100s %s";
  char ans1[100], ans2[100], ans3[100];
  char ans4[100], ans5[100], ans6[100];
  ck_assert(s21_sscanf(str, format, ans1, ans2, ans3) ==
            sscanf(str, format, ans4, ans5, ans6));
  ck_assert_str_eq(ans1, ans4);
  ck_assert_str_eq(ans2, ans5);
  ck_assert_str_eq(ans3, ans6);
}
END_TEST

static char dec_array_width[][100] = {
    "",    "b",     "0",      "00000",    "1",   "-1",    "70",
    "777", "11111", "11asdf", "-007  28", "088", "-0099", "+0"};

static int dec_answers_w[] = {0,   0,  0,  0, 1,  -1,  70,
                              777, 11, 11, 0, 88, -99, 0};

static int dec_size_width[] = {0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 3, 10, 50, 0};

static int dec_offset[] = {0, 0, 1, 5, 1, 2, 2, 3, 2, 2, 3, 3, 5, 2};

START_TEST(s21_scanf_parse_dec_width) {
  int offset = 0;
  int i = parse_dec(dec_array_width[_i], dec_size_width[_i], &offset);
  if (!(i == dec_answers_w[_i]))
    printf("result: %d || answer: %d\n", i, dec_answers_w[_i]);
  ck_assert(i == dec_answers_w[_i]);
  if (!(offset == dec_offset[_i]))
    printf("offset as is: %d || correct offset: %d\n", offset, dec_offset[_i]);
  ck_assert(offset == dec_offset[_i]);
}
END_TEST

static char hex_array[][100] = {"A",   "AA", "a",    "ff",    "1",    "a9m",
                                "0x8", "+b", "-0xb", "+0X55", "-000", "005"};

static int hex_answers[] = {10, 170, 10, 255, 1, 169, 8, 11, -11, 85, 0, 5};

static char hex_array_width[][100] = {
    "FFFF", "FFFF",      "-0xC",        "-0xC",           "-0xCC",
    "0xJJ", "-80000000", "+0x7fffffff", "\n\t  \n-0XEpmm"};

static int hex_answers_w[] = {255, 15,          0,          0,  -12,
                              0,   -2147483648, 2147483647, -14};

static int hex_size_width[] = {2, 1, 2, 3, 4, 3, 0, 0, 0};

static int hex_offset[] = {2, 1, 2, 3, 4, 2, 9, 11, 9};

START_TEST(s21_scanf_parse_hex) {
  int offset = 0;
  int i = parse_hex(hex_array[_i], 0, &offset);
  if (!(i == hex_answers[_i]))
    printf("result: %d || answer: %d\n", i, hex_answers[_i]);
  ck_assert(i == hex_answers[_i]);
}
END_TEST

START_TEST(s21_scanf_parse_hex_width) {
  int offset = 0;
  int i = parse_hex(hex_array_width[_i], hex_size_width[_i], &offset);
  if (!(i == hex_answers_w[_i]))
    printf("result: %d || answer: %d\n", i, hex_answers_w[_i]);
  ck_assert(i == hex_answers_w[_i]);
  if (!(offset == hex_offset[_i]))
    printf("offset as is: %d || correct offset: %d\n", offset, hex_offset[_i]);
  ck_assert(offset == hex_offset[_i]);
}
END_TEST

START_TEST(s21_sscanf_1) {
  char c1, c2;
  char inp[] = "asdf asdf";
  char format[] = "asdf%casdf";
  ck_assert(s21_sscanf(inp, format, &c1) == sscanf(inp, format, &c2));
}
END_TEST

START_TEST(s21_sscanf_2) {
  float c1, c2;
  char inp[] = "1e-11";
  char format[] = "%f";
  ck_assert(s21_sscanf(inp, format, &c1) == sscanf(inp, format, &c2));
}
END_TEST

static char oct_array_width[][100] = {"",      "b",      "0",        "00000",
                                      "1",     "-1",     "70",       "777",
                                      "11111", "11asdf", "-007  28", "088"};

static int oct_answers_w[] = {0, 0, 0, 0, 1, -1, 56, 511, 9, 9, 0, 0};

static int oct_size_width[] = {0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 3, 10};

static int oct_offset[] = {0, 0, 1, 5, 1, 2, 2, 3, 2, 2, 3, 1};

START_TEST(s21_scanf_parse_oct_width) {
  int offset = 0;
  int i = parse_oct(oct_array_width[_i], oct_size_width[_i], &offset);
  if (!(i == oct_answers_w[_i]))
    printf("result: %d || answer: %d\n", i, oct_answers_w[_i]);
  ck_assert(i == oct_answers_w[_i]);
  if (!(offset == oct_offset[_i]))
    printf("offset as is: %d || correct offset: %d\n", offset, oct_offset[_i]);
  ck_assert(offset == oct_offset[_i]);
}
END_TEST

START_TEST(s21_sscanf_3) {
  float c1, c2;
  char inp[] = "%@";
  char format[] = "%%%c";
  ck_assert(s21_sscanf(inp, format, &c1) == sscanf(inp, format, &c2));
}
END_TEST

START_TEST(s21_sscanf_4) {
  char buf1[100];
  char buf2[100];
  int n1, n2;
  char inp[] = "%@";
  char format[] = "%s%n";
  ck_assert(s21_sscanf(inp, format, buf1, &n1) ==
            sscanf(inp, format, buf2, &n2));
}
END_TEST

START_TEST(s21_sscanf_5) {
  void *p1;
  void *p2;
  char inp[] = "fafafafa";
  char format[] = "%p";
  ck_assert(s21_sscanf(inp, format, &p1) == sscanf(inp, format, &p2));
}
END_TEST

START_TEST(s21_sscanf_6) {
  char ch1[100];
  char ch2[100];
  char inp[] = "fafafafa\nnext";
  char format[] = "%*p %3s";
  ck_assert(s21_sscanf(inp, format, ch1) == sscanf(inp, format, ch2));
  ck_assert_str_eq(ch1, ch2);
}
END_TEST

START_TEST(s21_sscanf_7) {
  char ch1[100];
  char ch2[100];
  char inp[] = "fafafafa\vnext";
  char format[] = "%*s %3s";

  ck_assert(s21_sscanf(inp, format, ch1) == sscanf(inp, format, ch2));
  ck_assert_str_eq(ch1, ch2);
}
END_TEST
START_TEST(check_string_len_test) {
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("   "), strlen("   "));
  ck_assert_int_eq(s21_strlen("123456789"), strlen("123456789"));
  ck_assert_int_eq(s21_strlen("qw!er^ty"), strlen("qw!er^ty"));
  ck_assert_int_eq(s21_strlen("qwerty"), strlen("qwerty"));
  ck_assert_int_eq(s21_strlen("qwe321\000rty"), strlen("qwe321\000rty"));
  ck_assert_int_eq(s21_strlen("QwErTy!"), strlen("QwErTy!"));
}
END_TEST

START_TEST(check_strcspn_test) {
  ck_assert_int_eq(s21_strcspn("0123456789", "789"),
                   strcspn("0123456789", "789"));
  ck_assert_int_eq(s21_strcspn("abc", "123"), strcspn("abc", "123"));
  ck_assert_int_eq(s21_strcspn("abc3", "789"), strcspn("abc3", "789"));
  ck_assert_int_eq(s21_strcspn("0123456789", ""), strcspn("0123456789", ""));
  ck_assert_int_eq(s21_strcspn("0123456789", "789"),
                   strcspn("0123456789", "789"));
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
}
END_TEST

START_TEST(check_strncmp_test) {
  char temp1[] = "0123456789";
  ck_assert_int_eq(s21_strncmp(temp1, "0123456789", 5),
                   strncmp(temp1, "0123456789", 5));
  ck_assert_int_eq(s21_strncmp(temp1, "0123456", 5),
                   strncmp(temp1, "0123456", 5));
  ck_assert_int_eq(s21_strncmp(temp1, "0123", 4), strncmp(temp1, "0123", 4));
  char temp2[] = "01234\00056789";
  ck_assert_int_eq(s21_strncmp(temp2, "01234\00056789", 10),
                   strncmp(temp2, "01234\00056789", 10));
  char temp3[] = "01234\00077789";
  ck_assert_int_eq(s21_strncmp(temp3, "01234\00056789", 10),
                   strncmp(temp3, "01234\00056789", 10));
  char empty[10] = "";
  ck_assert_int_eq(s21_strncmp(empty, "", 5), strncmp(empty, "", 5));
  char temp4[] = "123";
  ck_assert_int_eq(s21_strncmp(temp4, "", 0), strncmp(temp4, "", 0));
  ck_assert_int_eq(s21_strncmp(temp4, "", 3), strncmp(temp4, "", 3));
  ck_assert_int_eq(s21_strncmp(temp4, "0123456", 4),
                   strncmp(temp4, "0123456", 4));
}
END_TEST

START_TEST(check_memcmp_test) {
  char nums[] = "0123456789";
  ck_assert_int_eq(s21_memcmp(nums, "0123456789", 5),
                   memcmp(nums, "0123456789", 5));
  ck_assert_int_eq(s21_memcmp(nums, "0123456789", 11),
                   memcmp(nums, "0123456789", 11));
  ck_assert_int_eq(s21_memcmp(nums, "0123456709", 5),
                   memcmp(nums, "0123456709", 5));
  ck_assert_int_eq(s21_memcmp(nums, "9123456789", 10) < 0,
                   memcmp(nums, "9123456789", 10) < 0);
  char temp1[] = "01234\000456789";
  ck_assert_int_eq(s21_memcmp(temp1, "0123\000456789", 10) > 0,
                   memcmp(temp1, "0123\000456789", 10) > 0);
  char temp2[] = "0123\000456689";
  ck_assert_int_eq(s21_memcmp(temp2, "0123\000477789", 10) < 0,
                   memcmp(temp2, "0123\000477789", 10) < 0);
}
END_TEST

START_TEST(check_strncpy_test) {
  char str1[] = "123\000456789", str2[] = "              ", str3[] = " ",
       str4[] = "qwertyuio";
  ck_assert_ptr_eq(s21_strncpy(str1, "1111111111", 11),
                   strncpy(str1, "1111111111", 11));
  ck_assert_ptr_eq(s21_strncpy(str1, "qwerty", 7), strncpy(str1, "qwerty", 7));
  ck_assert_ptr_eq(s21_strncpy(str1, "", 7), strncpy(str1, "", 7));
  ck_assert_ptr_eq(s21_strncpy(str2, "1111111111", 11),
                   strncpy(str2, "1111111111", 11));
  ck_assert_ptr_eq(s21_strncpy(str3, "", 1), strncpy(str3, "", 1));
  ck_assert_ptr_eq(s21_strncpy(str4, "111111111", 10),
                   strncpy(str4, "111111111", 10));
}
END_TEST

START_TEST(check_memcpy_test) {
  char str1[] = "12345\0006789", str2[] = "qwertyuiop", str3[] = "",
       str4[] = "    ";
  ck_assert_ptr_eq(s21_memcpy(str1, "1111111111", 3),
                   memcpy(str1, "1111111111", 3));
  ck_assert_ptr_eq(s21_memcpy(str1, "1111111111", 7),
                   memcpy(str1, "1111111111", 7));
  ck_assert_ptr_eq(s21_memcpy(str2, "1111111111", 10),
                   memcpy(str2, "1111111111", 10));
  ck_assert_ptr_eq(s21_memcpy(str1, "", 1), memcpy(str1, "", 1));
  ck_assert_ptr_eq(s21_memcpy(str3, "111", 1), memcpy(str3, "111", 1));
  ck_assert_ptr_eq(s21_memcpy(str4, "", 1), memcpy(str4, "", 1));
}
END_TEST

START_TEST(check_memset_test) {
  char str1[] = "0123456789", str2[] = "        ", str3[] = "12345567867213",
       str4[] = "0123456789";
  ck_assert_ptr_eq(s21_memset(str1, '1', 5), memset(str1, '1', 5));
  ck_assert_ptr_eq(s21_memset(str1, '0', 10), memset(str1, '0', 10));
  ck_assert_ptr_eq(s21_memset(str2, '1', 5), memset(str2, '1', 5));
  ck_assert_ptr_eq(s21_memset(str3, ' ', 5), memset(str3, ' ', 5));
  ck_assert_ptr_eq(s21_memset(str3, 'q', 1), memset(str3, 'q', 1));
  ck_assert_ptr_eq(s21_memset(str4, 'W', 10), memset(str4, 'W', 10));
}
END_TEST

START_TEST(check_string_trim) {
  const char *src = "123abc456xyz789";
  const char *trim_chars = "123456789";
  char *res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "abc456xyz");
  free(res);

  src = "123abc456xyz7890";
  trim_chars = "123456789";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "abc456xyz7890");
  free(res);

  src = "hello";
  trim_chars = "hello";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = "hello";
  trim_chars = "hello world!";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = "   hello   ";
  trim_chars = " ";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "hello");
  free(res);

  src = "   He llo, World !.   ";
  trim_chars = " .";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "He llo, World !");
  free(res);

  src = "";
  trim_chars = "";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = "";
  trim_chars = "hello";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = S21_NULL;
  trim_chars = "hello";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert(res == S21_NULL);

  src = "hello";
  trim_chars = S21_NULL;
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert(res == S21_NULL);

  src = S21_NULL;
  trim_chars = S21_NULL;
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert(res == S21_NULL);

  src = "b";
  trim_chars = "b";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = "bb";
  trim_chars = "b";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "");
  free(res);

  src = "bb";
  trim_chars = "a";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "bb");
  free(res);

  src = "Hello world!";
  trim_chars = "world";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "Hello world!");
  free(res);

  src = "Hello world!";
  trim_chars = "world!";
  res = (char *)(s21_trim(src, trim_chars));
  ck_assert_str_eq(res, "Hello ");
  free(res);
}
END_TEST

START_TEST(check_string_insert) {
  const char *src = "hello";
  const char *str = " world";
  s21_size_t start_index = 5;
  char *res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "hello world");
  free(res);

  src = "aaabbb";
  str = " ";
  start_index = 3;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "aaa bbb");
  free(res);

  src = "World";
  str = "Hello";
  start_index = 0;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "HelloWorld");
  free(res);

  src = "";
  str = "123";
  start_index = 0;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "123");
  free(res);

  src = "abc";
  str = "";
  start_index = 2;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "abc");
  free(res);

  src = "";
  str = "";
  start_index = 0;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert_str_eq(res, "");
  free(res);

  src = S21_NULL;
  str = "smth";
  start_index = 0;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert(res == S21_NULL);

  src = "smth";
  str = S21_NULL;
  start_index = 0;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert(res == S21_NULL);

  src = "World";
  str = "Hello";
  start_index = 6;
  res = (char *)(s21_insert(src, str, start_index));
  ck_assert(res == S21_NULL);
}
END_TEST

START_TEST(check_string_to_lower) {
  const char *str = "ABC";
  char *res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "abc");
  free(res);

  str = "abcABC!";
  res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "abcabc!");
  free(res);

  str = "abc";
  res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "abc");
  free(res);

  str = "123";
  res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "123");
  free(res);

  str = "XYZ123";
  res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "xyz123");
  free(res);

  str = "";
  res = (char *)(s21_to_lower(str));
  ck_assert_str_eq(res, "");
  free(res);

  str = S21_NULL;
  res = (char *)(s21_to_lower(str));
  ck_assert(res == S21_NULL);
}
END_TEST

START_TEST(check_string_to_upper) {
  const char *str = "abc";
  char *res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "ABC");
  free(res);

  str = "abcABC.";
  res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "ABCABC.");
  free(res);

  str = "ABC";
  res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "ABC");
  free(res);

  str = "123";
  res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "123");
  free(res);

  str = "xyz123";
  res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "XYZ123");
  free(res);

  str = "";
  res = (char *)(s21_to_upper(str));
  ck_assert_str_eq(res, "");
  free(res);

  str = S21_NULL;
  res = (char *)(s21_to_upper(str));
  ck_assert(res == S21_NULL);
}
END_TEST

START_TEST(check_sprintf) {
  char str1[20];
  char str2[20];
  int a = 10;

  ck_assert_int_eq(s21_sprintf(str1, "Text = %d\n", a),
                   sprintf(str2, "Text = %d\n", a));
  ck_assert_str_eq(str1, str2);

  char s1[150];
  char s2[150];
  a = 0;
  char c = 'M';
  float f = -10.10;
  char *str = "Hello world !";
  unsigned int u = 28;

  s21_sprintf(s1,
              "Int a = %d, char c = %c, float f = %f, str str = %s, uint u = "
              "%u, char %%",
              a, c, f, str, u);
  sprintf(s2,
          "Int a = %d, char c = %c, float f = %f, str str = %s, uint u = %u, "
          "char %%",
          a, c, f, str, u);
  ck_assert_int_eq(s21_sprintf(s1,
                               "Int a = %d, char c = %c, float f = %f, str str "
                               "= %s, uint u = %u, char %%",
                               a, c, f, str, u),
                   sprintf(s2,
                           "Int a = %d, char c = %c, float f = %f, str str = "
                           "%s, uint u = %u, char %%",
                           a, c, f, str, u));
  ck_assert_str_eq(s1, s2);

  a = -1234;
  ck_assert_int_eq(sprintf(s1, "%- 7dn", a), s21_sprintf(s2, "%- 7dn", a));
  ck_assert_str_eq(s1, s2);

  a = -1234;
  ck_assert_int_eq(sprintf(s1, "%+3dn", a), s21_sprintf(s2, "%+3dn", a));
  ck_assert_str_eq(s1, s2);

  a = -1234;
  ck_assert_int_eq(sprintf(s1, "% -3dn", a), s21_sprintf(s2, "% -3dn", a));
  ck_assert_str_eq(s1, s2);

  a = -1234;
  ck_assert_int_eq(sprintf(s1, "%+dn", a), s21_sprintf(s2, "%+dn", a));
  ck_assert_str_eq(s1, s2);

  a = 1234;
  ck_assert_int_eq(sprintf(s1, "% 100dn", a), s21_sprintf(s2, "% 100dn", a));
  ck_assert_str_eq(s1, s2);

  a = 1234;
  ck_assert_int_eq(sprintf(s1, "% -100dn", a), s21_sprintf(s2, "% -100dn", a));
  ck_assert_str_eq(s1, s2);

  ck_assert_int_eq(sprintf(s1, "n"), s21_sprintf(s2, "n"));
  ck_assert_str_eq(s1, s2);

  ck_assert_int_eq(sprintf(s1, " "), s21_sprintf(s2, " "));
  ck_assert_str_eq(s1, s2);

  f = 0.0001;
  ck_assert_int_eq(sprintf(s1, "% -100f", f), s21_sprintf(s2, "% -100f", f));
  ck_assert_str_eq(s1, s2);

  f = -0.0001;
  ck_assert_int_eq(sprintf(s1, "%+-f", f), s21_sprintf(s2, "%+-f", f));
  ck_assert_str_eq(s1, s2);

  f = -0.0001;
  ck_assert_int_eq(sprintf(s1, "%+-12f", f), s21_sprintf(s2, "%+-12f", f));
  ck_assert_str_eq(s1, s2);

  f = -9.99;
  ck_assert_int_eq(sprintf(s1, "%12f", f), s21_sprintf(s2, "%12f", f));
  ck_assert_str_eq(s1, s2);

  f = 1. / 3;
  ck_assert_int_eq(sprintf(s1, "% -12f", f), s21_sprintf(s2, "% -12f", f));
  ck_assert_str_eq(s1, s2);

  f = 1. / 3;
  ck_assert_int_eq(sprintf(s1, "%+11f", f), s21_sprintf(s2, "%+11f", f));
  ck_assert_str_eq(s1, s2);

  f = 1. / 3;
  ck_assert_int_eq(sprintf(s1, "float f = %+11f", f),
                   s21_sprintf(s2, "float f = %+11f", f));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(sprintf(s1, "str = %s", str),
                   s21_sprintf(s2, "str = %s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(sprintf(s1, "str = %15s", str),
                   s21_sprintf(s2, "str = %15s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(sprintf(s1, "str = %-15s", str),
                   s21_sprintf(s2, "str = %-15s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  f = 1.1;
  a = 1;
  ck_assert_int_eq(
      sprintf(s1, "str = %-15s, f = %+-10f, a = % 12d", str, f, a),
      s21_sprintf(s2, "str = %-15s, f = %+-10f, a = % 12d", str, f, a));
  ck_assert_str_eq(s1, s2);

  a = 123;
  ck_assert_int_eq(sprintf(s1, "% 100.2dn", a),
                   s21_sprintf(s2, "% 100.2dn", a));
  ck_assert_str_eq(s1, s2);

  a = -12;
  ck_assert_int_eq(sprintf(s1, "%+100.100dn", a),
                   s21_sprintf(s2, "%+100.100dn", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "% -3.100d", a),
                   s21_sprintf(s2, "% -3.100d", a));
  ck_assert_str_eq(s1, s2);

  a = -1;
  ck_assert_int_eq(sprintf(s1, "% -3.0d", a), s21_sprintf(s2, "% -3.0d", a));
  ck_assert_str_eq(s1, s2);

  a = 123;
  ck_assert_int_eq(sprintf(s1, "%3.00d", a), s21_sprintf(s2, "%3.00d", a));
  ck_assert_str_eq(s1, s2);

  a = 123;
  ck_assert_int_eq(sprintf(s1, "%+3.0000000012d", a),
                   s21_sprintf(s2, "%+3.0000000012d", a));
  ck_assert_str_eq(s1, s2);

  a = -12;
  ck_assert_int_eq(sprintf(s1, "% 20.0000000012d", a),
                   s21_sprintf(s2, "% 20.0000000012d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "% 2.0d", a), s21_sprintf(s2, "% 2.0d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "% 2d", a), s21_sprintf(s2, "% 2d", a));
  ck_assert_str_eq(s1, s2);

  a = 1;
  ck_assert_int_eq(sprintf(s1, "% 2.0d", a), s21_sprintf(s2, "% 2.0d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "% 2.1d", a), s21_sprintf(s2, "% 2.1d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "% 2.d", a), s21_sprintf(s2, "% 2.d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "%+2.d", a), s21_sprintf(s2, "%+2.d", a));
  ck_assert_str_eq(s1, s2);

  a = 1;
  ck_assert_int_eq(sprintf(s1, "%+2.2d", a), s21_sprintf(s2, "%+2.2d", a));
  ck_assert_str_eq(s1, s2);

  a = 0;
  ck_assert_int_eq(sprintf(s1, "%+2.5d", a), s21_sprintf(s2, "%+2.5d", a));
  ck_assert_str_eq(s1, s2);

  f = 123.456;
  ck_assert_int_eq(sprintf(s1, "%10.3f", f), s21_sprintf(s2, "%10.3f", f));
  ck_assert_str_eq(s1, s2);

  f = 123.0;
  ck_assert_int_eq(sprintf(s1, "%10.18f", f), s21_sprintf(s2, "%10.18f", f));
  ck_assert_str_eq(s1, s2);

  f = 123.456;
  ck_assert_int_eq(sprintf(s1, "% 10.3f", f), s21_sprintf(s2, "% 10.3f", f));
  ck_assert_str_eq(s1, s2);

  f = 123.456;
  ck_assert_int_eq(sprintf(s1, "%+10.10f", f), s21_sprintf(s2, "%+10.10f", f));
  ck_assert_str_eq(s1, s2);

  f = 0;
  ck_assert_int_eq(sprintf(s1, "%.f", f), s21_sprintf(s2, "%.f", f));
  ck_assert_str_eq(s1, s2);

  f = 0.1;
  ck_assert_int_eq(sprintf(s1, "%.5f", f), s21_sprintf(s2, "%.5f", f));
  ck_assert_str_eq(s1, s2);

  f = 0.000009;
  ck_assert_int_eq(sprintf(s1, "%-15.5f", f), s21_sprintf(s2, "%-15.5f", f));
  ck_assert_str_eq(s1, s2);

  f = 0.000009;
  ck_assert_int_eq(sprintf(s1, "%+-15.1f", f), s21_sprintf(s2, "%+-15.1f", f));
  ck_assert_str_eq(s1, s2);

  f = 0;
  ck_assert_int_eq(sprintf(s1, "%10.f", f), s21_sprintf(s2, "%10.f", f));
  ck_assert_str_eq(s1, s2);

  f = 0;
  ck_assert_int_eq(sprintf(s1, "%10.2f", f), s21_sprintf(s2, "%10.2f", f));
  ck_assert_str_eq(s1, s2);

  f = 0;
  ck_assert_int_eq(sprintf(s1, "%-10.8f", f), s21_sprintf(s2, "%-10.8f", f));
  ck_assert_str_eq(s1, s2);

  f = 9.9;
  ck_assert_int_eq(sprintf(s1, "%-10.8f", f), s21_sprintf(s2, "%-10.8f", f));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%-15.1sn", str),
                   sprintf(s2, "%-15.1sn", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%-15.10s", str),
                   sprintf(s2, "%-15.10s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%15.10sn", str),
                   sprintf(s2, "%15.10sn", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%5.10s", str), sprintf(s2, "%5.10s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%-5.10sn", str),
                   sprintf(s2, "%-5.10sn", str));
  ck_assert_str_eq(s1, s2);

  str = "";
  ck_assert_int_eq(s21_sprintf(s1, "%-5.10s", str),
                   sprintf(s2, "%-5.10s", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%-5.sn", str), sprintf(s2, "%-5.sn", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%-25.10snlop", str),
                   sprintf(s2, "%-25.10snlop", str));
  ck_assert_str_eq(s1, s2);

  str = "Hello world !";
  ck_assert_int_eq(s21_sprintf(s1, "%%%-25.10snlop", str),
                   sprintf(s2, "%%%-25.10snlop", str));
  ck_assert_str_eq(s1, s2);

  short sh = 10000;
  str = "";
  ck_assert_int_eq(s21_sprintf(s1, "%-10.03hd %-10.20s", sh, str),
                   sprintf(s2, "%-10.03hd %-10.20s", sh, str));
  ck_assert_str_eq(s1, s2);

  a = 123456;
  str = "D\t/g/h";
  char *pat = "%-0.3d hello %-10.s world";
  ck_assert_int_eq(s21_sprintf(s1, pat, a, str), sprintf(s2, pat, a, str));
  ck_assert_str_eq(s1, s2);

  a = 123456;
  str = "D\t/g/h";
  pat = "%-+ --0.3d hello %---++10.3s world";
  ck_assert_int_eq(s21_sprintf(s1, pat, a, str), sprintf(s2, pat, a, str));
  ck_assert_str_eq(s1, s2);

  f = 1.01;
  ck_assert_int_eq(s21_sprintf(s1, "%10.000010f", f),
                   sprintf(s2, "%10.000010f", f));
  ck_assert_str_eq(s1, s2);

  str = "Hello";
  f = -9.98;
  short int l = 10;
  pat = "str = %10.10s, f = %-10.3f, l = %10hd ";
  ck_assert_int_eq(s21_sprintf(s1, pat, str, f, l),
                   sprintf(s2, pat, str, f, l));
  ck_assert_str_eq(s1, s2);

  str = "";
  ck_assert_int_eq(s21_sprintf(s1, "%s", str), sprintf(s2, "%s", str));
  ck_assert_str_eq(s1, s2);

  char ss1[13];
  char ss2[13];
  pat = "%s%f";
  ck_assert_int_eq(s21_sprintf(ss1, pat, "text", 1.4),
                   sprintf(ss2, pat, "text", 1.4));
  ck_assert_str_eq(ss1, ss2);

  long int aa = 9223372036854775806;
  pat = "%ld";
  ck_assert_int_eq(s21_sprintf(s1, pat, aa), sprintf(s2, pat, aa));
  ck_assert_str_eq(s1, s2);

  aa = 9223372036854775806;
  pat = "%10.40ld";
  ck_assert_int_eq(s21_sprintf(s1, pat, aa), sprintf(s2, pat, aa));
  ck_assert_str_eq(s1, s2);

  pat = "%012.002d";
  a = 1;
  ck_assert_int_eq(s21_sprintf(s1, pat, a), sprintf(s2, pat, a));
  ck_assert_str_eq(s1, s2);

  pat = "%+++---- 012.002d";
  a = 0;
  ck_assert_int_eq(s21_sprintf(s1, pat, a), sprintf(s2, pat, a));
  ck_assert_str_eq(s1, s2);

  unsigned long aaa = 9223372036854775806;
  pat = "%10.40lu";
  ck_assert_int_eq(s21_sprintf(s1, pat, aaa), sprintf(s2, pat, aaa));
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(sprintf_simple_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "This is a simple value %d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_width_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_plus_width_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_padding_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%12u";
  unsigned int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_star_width_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_long_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%+5.31ld";
  long int val = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_short_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%-16.9hd";
  short int val = 6958;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_flags_another_long_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%0.ld";
  long val = 8581385185;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_zero_precision_zero_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%.0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_space_flag_int) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_width) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_precision) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_short) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_long) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_val_many) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_dec_short) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_unsigned_zero) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_char) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_one_precision) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_width) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_many) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_one_many_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_precision) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%.15s";
  char *val = "I LOVE STRINGS AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_width) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_long) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_many) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string_width_huge) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_zero) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *format = "%.0f";
  double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_empty) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *format = "%.f";
  double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_huge) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *format = "%.15f";
  double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_precision_huge_negative) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *format = "%.15f";
  double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_float_flags) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_all_empty) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_empty_format_and_parameters) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_char) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_string) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_string) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(
      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_dec) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_dec) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_float) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.000), sprintf(str2, "%f", 0.000));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_float) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  ck_assert_int_eq(
      s21_sprintf(str1, "%f%f%f%f", -999.666, 0.000, 666.999, -100.001),
      sprintf(str2, "%f%f%f%f", -999.666, 0.000, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_unsigned_dec) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char_with_alignment_left) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_one_char_with_alignment_right) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_many_char_with_alignment) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf1) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf2) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf3) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf4) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%+5.5d aboba";

  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf6) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%7.7f";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                   sprintf(str2, format, 11.123456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf7) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%7.4s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                   sprintf(str2, format, "aboba floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf8) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                   sprintf(str2, format, 12341151));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf9) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%ld%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
                   sprintf(str2, format, 666666666666, 777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf10) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%hd%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                   sprintf(str2, format, 666, -777, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf16) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf17) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba likes floppa"),
                   sprintf(str2, format, "aboba likes floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf18) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'),
                   sprintf(str2, format, "", 'f'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf19) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));

  ck_assert_str_eq(str1, str2);
}

START_TEST(sprintf_test_sprintf20) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                   sprintf(str2, format, "Nick her"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf24) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%+2.1c%+4.2d%+5.4d%+10.2f%+55.55s%+1.1hu";

  ck_assert_int_eq(
      s21_sprintf(str1, format, 'f', 21, 42, 666.666,
                  "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11),
      sprintf(str2, format, 'f', 21, 42, 666.666,
              "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf29) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_sprintf30) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_ld_negative_num) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  char format[] = "%8ld";
  long val = -435373;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_percent) {
  char str1[SIZE] = {'\0'};
  char str2[SIZE] = {'\0'};

  ck_assert_int_eq(s21_sprintf(str1, "hello its percent symb = %%"),
                   sprintf(str2, "hello its percent symb = %%"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");

  TCase *tc_sprintf = tcase_create("TEST SPRINTF");
  tcase_add_test(tc_sprintf, check_sprintf);
  tcase_add_test(tc_sprintf, sprintf_simple_int);

  tcase_add_test(tc_sprintf, sprintf_width_int);

  tcase_add_test(tc_sprintf, sprintf_plus_width_int);
  tcase_add_test(tc_sprintf, sprintf_padding_int);
  tcase_add_test(tc_sprintf, sprintf_star_width_int);

  tcase_add_test(tc_sprintf, sprintf_flags_long_int);
  tcase_add_test(tc_sprintf, sprintf_flags_short_int);
  tcase_add_test(tc_sprintf, sprintf_flags_another_long_int);
  tcase_add_test(tc_sprintf, sprintf_zero_precision_zero_int);
  tcase_add_test(tc_sprintf, sprintf_space_flag_int);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_width);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_flags);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_precision);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_many_flags);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_short);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_long);
  tcase_add_test(tc_sprintf, sprintf_unsigned_val_many);

  tcase_add_test(tc_sprintf, sprintf_dec_short);

  tcase_add_test(tc_sprintf, sprintf_unsigned_zero);
  tcase_add_test(tc_sprintf, sprintf_one_char);
  tcase_add_test(tc_sprintf, sprintf_one_precision);
  tcase_add_test(tc_sprintf, sprintf_one_flags);
  tcase_add_test(tc_sprintf, sprintf_one_width);
  tcase_add_test(tc_sprintf, sprintf_one_many);
  tcase_add_test(tc_sprintf, sprintf_one_many_flags);
  tcase_add_test(tc_sprintf, sprintf_string);
  tcase_add_test(tc_sprintf, sprintf_string_precision);
  tcase_add_test(tc_sprintf, sprintf_string_width);
  tcase_add_test(tc_sprintf, sprintf_string_flags);
  tcase_add_test(tc_sprintf, sprintf_string_long);
  tcase_add_test(tc_sprintf, sprintf_string_many);

  tcase_add_test(tc_sprintf, sprintf_string_width_huge);

  tcase_add_test(tc_sprintf, sprintf_float_precision_zero);
  tcase_add_test(tc_sprintf, sprintf_float_precision_empty);
  tcase_add_test(tc_sprintf, sprintf_float_precision_huge);
  tcase_add_test(tc_sprintf, sprintf_float_precision_huge_negative);

  tcase_add_test(tc_sprintf, sprintf_float_flags);

  tcase_add_test(tc_sprintf, sprintf_all_empty);
  tcase_add_test(tc_sprintf, sprintf_empty_format_and_parameters);
  tcase_add_test(tc_sprintf, sprintf_test_one_char);
  tcase_add_test(tc_sprintf, sprintf_test_many_char);
  tcase_add_test(tc_sprintf, sprintf_test_one_string);
  tcase_add_test(tc_sprintf, sprintf_test_many_string);
  tcase_add_test(tc_sprintf, sprintf_test_one_dec);
  tcase_add_test(tc_sprintf, sprintf_test_many_dec);

  tcase_add_test(tc_sprintf, sprintf_test_one_float);
  tcase_add_test(tc_sprintf, sprintf_test_many_float);
  tcase_add_test(tc_sprintf, sprintf_test_one_unsigned_dec);
  tcase_add_test(tc_sprintf, sprintf_test_one_char_with_alignment_left);
  tcase_add_test(tc_sprintf, sprintf_test_one_char_with_alignment_right);
  tcase_add_test(tc_sprintf, sprintf_test_many_char_with_alignment);

  tcase_add_test(tc_sprintf, sprintf_test_sprintf1);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf2);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf3);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf4);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf6);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf7);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf8);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf9);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf10);

  tcase_add_test(tc_sprintf, sprintf_test_sprintf16);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf17);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf18);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf19);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf20);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf24);

  tcase_add_test(tc_sprintf, sprintf_test_sprintf29);
  tcase_add_test(tc_sprintf, sprintf_test_sprintf30);

  tcase_add_test(tc_sprintf, sprintf_ld_negative_num);

  tcase_add_test(tc_sprintf, sprintf_percent);

  suite_add_tcase(s1, tc_sprintf);

  TCase *tc_trim = tcase_create("TEST TRIM");
  tcase_add_test(tc_trim, check_string_trim);
  suite_add_tcase(s1, tc_trim);

  TCase *tc_insert = tcase_create("TEST INSERT");
  tcase_add_test(tc_insert, check_string_insert);
  suite_add_tcase(s1, tc_insert);

  TCase *tc_to_lower = tcase_create("TEST TO_LOWER");
  tcase_add_test(tc_to_lower, check_string_to_lower);
  suite_add_tcase(s1, tc_to_lower);

  TCase *tc_to_upper = tcase_create("TEST TO_UPPER");
  tcase_add_test(tc_to_upper, check_string_to_upper);
  suite_add_tcase(s1, tc_to_upper);

  TCase *tc_strl = tcase_create("strlen");

  tcase_add_test(tc_strl, s21_memchr_test);
  tcase_add_test(tc_strl, s21_strchr_test);
  tcase_add_test(tc_strl, s21_strrchr_test);
  tcase_add_test(tc_strl, s21_strpbrk_test);
  tcase_add_test(tc_strl, s21_strstr_tets);
  tcase_add_test(tc_strl, s21_strerror_test);
  tcase_add_test(tc_strl, s21_strncat_test);
  tcase_add_test(tc_strl, s21_strtok_test);

  suite_add_tcase(s1, tc_strl);

  TCase *tc_empt = tcase_create("strlen_empty");
  tcase_add_test(tc_empt, check_string_len_test);
  tcase_add_test(tc_empt, check_strcspn_test);
  tcase_add_test(tc_empt, check_strncmp_test);
  tcase_add_test(tc_empt, check_memcmp_test);
  tcase_add_test(tc_empt, check_strncpy_test);
  tcase_add_test(tc_empt, check_memcpy_test);
  tcase_add_test(tc_empt, check_memset_test);
  suite_add_tcase(s1, tc_empt);

  TCase *tc1_1 = tcase_create("s21_sscanf");
  TCase *tc1_2 = tcase_create("dec_parser");
  TCase *tc1_3 = tcase_create("hex_parser");
  TCase *tc1_4 = tcase_create("oct_parser");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_sscanf_1);
  tcase_add_test(tc1_1, s21_sscanf_2);
  tcase_add_test(tc1_1, s21_sscanf_3);
  tcase_add_test(tc1_1, s21_sscanf_4);
  tcase_add_test(tc1_1, s21_sscanf_5);
  tcase_add_test(tc1_1, s21_sscanf_6);
  tcase_add_test(tc1_1, s21_sscanf_7);
  tcase_add_test(tc1_1, test_s_21_sscanf_d0);
  tcase_add_test(tc1_1, test_s_21_sscanf_d1);
  tcase_add_test(tc1_1, test_s_21_sscanf_d2);
  tcase_add_test(tc1_1, test_s_21_sscanf_d3);
  tcase_add_test(tc1_1, test_s_21_sscanf_d4);
  tcase_add_test(tc1_1, test_s_21_sscanf_d5);
  tcase_add_test(tc1_1, test_s_21_sscanf_d6);
  tcase_add_test(tc1_1, test_s_21_sscanf_d7);
  tcase_add_test(tc1_1, test_s_21_sscanf_d8);
  tcase_add_test(tc1_1, test_s_21_sscanf_d9);
  tcase_add_test(tc1_1, test_s_21_sscanf_d10);
  tcase_add_test(tc1_1, test_s_21_sscanf_d11);
  tcase_add_test(tc1_1, test_s_21_sscanf_o1);
  tcase_add_test(tc1_1, test_s_21_sscanf_o2);
  tcase_add_test(tc1_1, test_s_21_sscanf_o3);
  tcase_add_test(tc1_1, test_s_21_sscanf_o4);
  tcase_add_test(tc1_1, test_s_21_sscanf_c5);
  tcase_add_test(tc1_1, test_s_21_sscanf_x1);
  tcase_add_test(tc1_1, test_s_21_sscanf_x2);
  tcase_add_test(tc1_1, test_s_21_sscanf_x3);
  tcase_add_test(tc1_1, test_s_21_sscanf_x4);
  tcase_add_test(tc1_1, test_s_21_sscanf_x5);
  tcase_add_test(tc1_1, test_s_21_sscanf_i1);
  tcase_add_test(tc1_1, test_s_21_sscanf_f1);
  tcase_add_test(tc1_1, test_s_21_sscanf_f2);
  tcase_add_test(tc1_1, test_s_21_sscanf_s1);
  tcase_add_test(tc1_1, test_s_21_sscanf_s2);
  tcase_add_test(tc1_1, test_s_21_sscanf_s3);
  suite_add_tcase(s1, tc1_2);
  tcase_add_loop_test(tc1_2, s21_scanf_parse_dec_width, 0, 14);
  suite_add_tcase(s1, tc1_3);
  tcase_add_loop_test(tc1_3, s21_scanf_parse_hex, 0, 12);
  tcase_add_loop_test(tc1_3, s21_scanf_parse_hex_width, 0, 9);
  suite_add_tcase(s1, tc1_4);
  tcase_add_loop_test(tc1_4, s21_scanf_parse_oct_width, 0, 12);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
