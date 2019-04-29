#ifndef WSCORE_GLOBAL_H
#define WSCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WSCORE_LIB
# define WSCORE_EXPORT Q_DECL_EXPORT
#else
# define WSCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // WSCORE_GLOBAL_H
