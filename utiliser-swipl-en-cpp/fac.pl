fac(1,1):- !.
fac(X,F):-
  X > 1,
  Y is X - 1,
  fac( Y, Next ),
  F is X * Next.

% ?- fac(3, X).