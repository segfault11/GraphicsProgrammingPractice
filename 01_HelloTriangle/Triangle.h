/*!
** A 2D Triangle that is drawable.
**	
** @file Triangle.h
** @since 2013-08-15
*/
#ifndef TRIANGLE_H__
#define TRIANGLE_H__

#include "Framework/IDrawable.h"
#include "Framework/Program.h"
#include "Framework/BufferObject.h"
#include "Framework/VertexArray.h"

class Triangle : public IDrawable
{
public:
    Triangle();
    ~Triangle();

    void Draw() const;

private:
    Program* program_;
    BufferObject* buffer_;
    BufferObject* colors_;
    VertexArray* vertexArray_;
    // GLuint buffer_;
    // GLuint vao_;
};


 
#endif /* end of include guard: TRIANGLE_H__ */
