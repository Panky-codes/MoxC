// C-API.h
#ifndef C_API_H_
#define C_API_H_

#ifdef __cplusplus
extern "C" {
#endif

struct c_api_cookie {
  int var1;
  float var2;
};


int c_api_func1(struct c_api_cookie *cookie, const char *str, int len);

int c_api_func2(int len);

void c_api_end(struct c_api_cookie *);

#ifdef __cplusplus
}
#endif

#endif // C_API_H_
