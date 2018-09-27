#ifndef MACROS_H
#define MACROS_H

#ifdef _DEBUG
#define trace(...) printf(__VA_ARGS__)
#else
#define trace(...) (void)0;
#endif

#define error(...) fprintf(stderr, __VA_ARGS__)

#endif