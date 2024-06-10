#if !defined(SHIZU_RUNTIME_COMPILER_AST_H_INCLUDED)
#define SHIZU_RUNTIME_COMPILER_AST_H_INCLUDED

#include "Shizu/Runtime/Compiler/Object.h"

typedef enum Shizu_Runtime_Compiler_AstType Shizu_Runtime_Compiler_AstType;

enum Shizu_Runtime_Compiler_AstType {
  Shizu_Runtime_Compiler_AstType_ClassDef,
  Shizu_Runtime_Compiler_AstType_MethodDef,
  Shizu_Runtime_Compiler_AstType_ConstructorDef,
};

Shizu_declareType(Shizu_Runtime_Compiler_Ast)

struct Shizu_Runtime_Compiler_Ast_Dispatch {
  Shizu_Runtime_Compiler_Object_Dispatch _parent;
};

struct Shizu_Runtime_Compiler_Ast {
  Shizu_Runtime_Compiler_Object _parent;
};

void
Shizu_Runtime_Compiler_Ast_construct
  (
    Shizu_State* state,
    Shizu_Runtime_Compiler_Ast* self
  );

#endif // SHIZU_RUNTIME_COMPILER_AST_H_INCLUDED