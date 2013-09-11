/*!
** Error handling class.
**    
** @since 2013-08-19
*/
#ifndef ERROR_H__
#define ERROR_H__

#define ERROR_REPORT(x) Error::Report(__FILE__, __LINE__, x);
#define ERROR_WARNING(x) Error::Warning(__FILE__, __LINE__, x);


class Error
{
public:
    static void Report(const char* filename, int line, const char* message);
    static void Warning(const char* filename, int line, const char* message);  
      
private:
    Error();
    ~Error();

};

#endif /* end of include guard: ERROR_H__ */