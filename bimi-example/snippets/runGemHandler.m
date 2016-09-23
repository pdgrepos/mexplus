%% ???
% - add name (ID) to constructor

function runGemHandler

  clc

%% Create a new GemHandler object
  gh = GemHandler() ;

%% Scalars test
  disp('==========   Put scalars   ==========')
  if ( gh.put('scalar.bool', true)              ) ; disp('INFO: put bool ok.')   ; end
  if ( gh.put('scalar.long', int32(42))         ) ; disp('INFO: put long ok.')   ; end
  if ( gh.put('scalar.date', datetime('today')) ) ; disp('INFO: put date ok.')   ; end
  if ( gh.put('scalar.double', 42.42)           ) ; disp('INFO: put double ok.') ; end
  if ( gh.put('scalar.string', 'mystring')      ) ; disp('INFO: put string ok.') ; end

  disp('==========   Read scalars   ==========')
  b = gh.get('scalar.bool')     ; if ( isscalar(b) && islogical(b)    ) ; disp('INFO: get bool ok.')   ; end
  l = gh.get('scalar.long')     ; if ( isscalar(l) && isa(l,'int32')  ) ; disp('INFO: get long ok.')   ; end
  t = gh.getDate('scalar.date') ; if ( isscalar(t) && isdatetime(t)   ) ; disp('INFO: get date ok.')   ; end
  d = gh.get('scalar.double')   ; if ( isscalar(d) && isa(d,'double') ) ; disp('INFO: get double ok.') ; end
  s = gh.get('scalar.string')   ; if ( ischar(s)   && isvector(s)     ) ; disp('INFO: get string ok.') ; end

%% Vectors test
  disp('==========   Put vectors   ==========')
  if ( gh.put('vector.bool', [ true false true])                                           ) ; disp('INFO: put vec-bool ok.')   ; end
  if ( gh.put('vector.long', [ int32(41) ; int32(42) ; int32(43) ])                        ) ; disp('INFO: put vec-long ok.')   ; end
  if ( gh.put('vector.date', [ datetime('now') datetime('tomorrow') datetime(2016,1,15) ]) ) ; disp('INFO: put vec-date ok.')   ; end
  if ( gh.put('vector.double', [ 41.41 ; 42.42 ; 43.43 ])                                  ) ; disp('INFO: put vec-double ok.') ; end
  if ( gh.put('vector.string', { 'aa' 'bbb' 'cccc' })                                      ) ; disp('INFO: put vec-string ok.') ; end

  disp('==========   Read vectors   ==========')
  vb = gh.get('vector.bool')     ; if ( isvector(vb) && islogical(vb)    ) ; disp('INFO: get vec-bool ok.')   ; end
  vl = gh.get('vector.long')     ; if ( isvector(vl) && isa(vl,'int32')  ) ; disp('INFO: get vec-long ok.')   ; end
  vt = gh.getDate('vector.date') ; if ( isvector(vt) && isdatetime(vt)   ) ; disp('INFO: get vec-date ok.')   ; end
  vd = gh.get('vector.double')   ; if ( isvector(vd) && isa(vd,'double') ) ; disp('INFO: get vec-double ok.') ; end
  vs = gh.get('vector.string')   ; if ( iscellstr(vs)                    ) ; disp('INFO: get vec-string ok.') ; end

%% Matrices test
  disp('==========   Put Matrices   ==========')
  if ( gh.put('matrix.bool', [ true false ; true false])                                                         ) ; disp('INFO: mat vec-bool ok.')   ; end
  if ( gh.put('matrix.long', [ int32(41) int32(42) ; int32(43) int32(44) ])                                      ) ; disp('INFO: mat vec-long ok.')   ; end
  if ( gh.put('matrix.date', [ datetime('now') datetime('tomorrow') ; datetime(2016,1,15) datetime(2017,6,15) ]) ) ; disp('INFO: mat vec-date ok.')   ; end
  if ( gh.put('matrix.double', [ 41.41 42.42 ; 43.43 44.44 ])                                                    ) ; disp('INFO: mat vec-double ok.') ; end
%  if ( gh.put('matrix.string', { 'aa' 'bbb' 'cccc' })                                      ) ; disp('INFO: put vec-string ok.') ; end

  disp('==========   Read Matrices   ==========')
  %mb = gh.get('matrix.bool')     ; if ( istruematrix(mb) && islogical(mb)    ) ; disp('INFO: get mat-bool ok.')   ; end
  %ml = gh.get('matrix.long')     ; if ( istruematrix(ml) && isa(ml,'int32')  ) ; disp('INFO: get mat-long ok.')   ; end
  %mt = gh.getDate('matrix.date') ; if ( istruematrix(mt) && isdatetime(mt)   ) ; disp('INFO: get mat-date ok.')   ; end
  %md = gh.get('matrix.double')   ; if ( istruematrix(md) && isa(md,'double') ) ; disp('INFO: get mat-double ok.') ; end
  %ms = gh.get('matrix.string')   ; if ( iscellstr(vs)                    ) ; disp('INFO: get vec-string ok.') ; end


%% Destroy the GemHandler object
  clear gh;

  disp('==========   Summary Report   ==========')
  arrayfun(@(x) disp([x.name ': ' x.class '(' num2str(x.size(1)) 'x' num2str(x.size(2)) ')' ]),whos)

end

function tf = istruematrix(value)
  tf = ismatrix(value) && all(size(value)>1) ;
end
