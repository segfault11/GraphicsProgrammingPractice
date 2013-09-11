/*!
** Error handling methods.
**    
** @since 2013-08-19
*/
#ifndef ERROR_H__
#define ERROR_H__

#define ERROR_REPORT(x) ERR::Report(__FILE__, __LINE__, x);
#define ERROR_WARNING(x) ERR::Warning(__FILE__, __LINE__, x);
#define ERROR_ASSERT(x) if (x) {} else {ERR::Assert(#x, __FILE__, __LINE__);}


namespace ERR
{
    void Report(const char* filename, int line, const char* message);
    void Warning(const char* filename, int line, const char* message);  
    void Assert(const char* expr, const char* filename, int line);
}

#endif /* end of include guard: ERROR_H__ */