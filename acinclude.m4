dnl Believe it or not, all these functions are needed to determine the type of
dnl accept()'s third parameter.
dnl I will take care of this code soon ...

AC_DEFUN([AC_PROTOTYPE],[
 pushdef([function],translit([$1], [a-z], [A-Z]))
 pushdef([tags],[AC_PROTOTYPE_TAGS(builtin([shift],builtin([shift],builtin([shift],$@))))])
 for i in 1
 do
   AC_PROTOTYPE_LOOP(AC_PROTOTYPE_REVERSE($1, AC_PROTOTYPE_SUBST($2,tags),AC_PROTOTYPE_SUBST($3, tags),builtin([shift],builtin([shift],builtin([shift],$@)))))
   AC_MSG_ERROR($1 unable to find a working combination)
 done
 popdef([tags])
 popdef([function])
])

AC_DEFUN([AC_PROTOTYPE_REVERSE],[ifelse($#,0,,$#,1,[[$1]],[AC_PROTOTYPE_REVERSE(builtin([shift],$@)),[$1]])])

AC_DEFUN([AC_PROTOTYPE_SUBST],[ifelse($2,,[$1],[AC_PROTOTYPE_SUBST(patsubst([$1],[$2],[$2[]_VAL]),builtin([shift],builtin([shift],$@)))])])

AC_DEFUN([AC_PROTOTYPE_TAGS],[ifelse($1,,[],[$1, AC_PROTOTYPE_TAGS(builtin([shift],builtin([shift],$@)))])])
AC_DEFUN([AC_PROTOTYPE_DEFINES],[ifelse($1,,[],[AC_DEFINE(function[]_$1, $1_VAL) AC_PROTOTYPE_DEFINES(builtin([shift],$@))])])

AC_DEFUN([AC_PROTOTYPE_STATUS],[ifelse($1,,[],[$1 => $1_VAL AC_PROTOTYPE_STATUS(builtin([shift],$@))])])

AC_DEFUN([AC_PROTOTYPE_EACH],[
  ifelse($2,, [
  ], [
    pushdef([$1_VAL], $2)
    AC_PROTOTYPE_LOOP(rest)
    popdef([$1_VAL])
    AC_PROTOTYPE_EACH($1, builtin([shift], builtin([shift], $@)))
  ])
])

AC_DEFUN([AC_PROTOTYPE_LOOP],[
  ifelse(builtin([eval], $# > 3), 1,
  [
    pushdef([rest],[builtin([shift],builtin([shift],$@))])
    AC_PROTOTYPE_EACH($2,$1)
    popdef([rest])
  ], [
    AC_MSG_CHECKING($3 AC_PROTOTYPE_STATUS(tags))
    ac_save_CPPFLAGS="$CPPFLAGS"
    ifelse(AC_LANG(C++),,if test "$GXX" = "yes" ; then CPPFLAGS="$CPPFLAGS -Werror" ; fi)
    ifelse(AC_LANG(C),,if test "$GCC" = "yes" ; then CPPFLAGS="$CPPFLAGS -Werror" ; fi)
    AC_TRY_COMPILE($2, $1, [
      CPPFLAGS="$ac_save_CPPFLAGS"
      AC_MSG_RESULT(ok)
      AC_PROTOTYPE_DEFINES(tags)
      break;
    ], [
      CPPFLAGS="$ac_save_CPPFLAGS"
      AC_MSG_RESULT(not ok)
    ])
  ]
 )
])

AC_DEFUN([AC_PROTOTYPE_ACCEPT],[
AC_PROTOTYPE(accept,
 [
  #include <sys/types.h>
  #include <sys/socket.h>
 ],
 [
  int a = 0;
  ARG2 * b = 0;
  ARG3 * c = 0;
  accept(a, b, c);
 ],
 ARG2, [struct sockaddr, void],
 ARG3, [socklen_t, size_t, int, unsigned int, long unsigned int])
])

