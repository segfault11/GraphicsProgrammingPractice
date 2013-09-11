/*!
** Interface drawable objects have to implement.
**
** @file IDrawable.h	
** @since 2013-08-15 
*/
#ifndef IDRAWABLE_H__
#define IDRAWABLE_H__
 
class IDrawable
{
public:
	virtual void Draw() const = 0;
};
 
#endif /* end of include guard: IDRAWABLE_H__ */