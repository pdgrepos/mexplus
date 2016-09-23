classdef GemHandler < handle

%% Public Static Methods
  methods (Access = public, Static)

    % Clear all session objects
    function ok = Clear()
      ok = GemHandler_('clear');
    end

  end

%% Public Instance Methods
  methods (Access = public)

    % Constructor
    function this = GemHandler()
      this.id_ = GemHandler_('new') ;
    end

    % Destructor
    function delete(this)
      GemHandler_('delete', this.id_);
    end

    % Polimorfic PUT. Retruns true on successful operation
    function ok = put(this, key, value)

      assert(ischar(key), 'KEY must be a string.');

      switch class(value)
        case 'logical'
          ok = BoolHandler(this, key, value) ;
        case 'int32'
          ok = LongHandler(this, key, value) ;
        case 'datetime'
          ok = DateHandler(this, key, value) ;
        case 'double'
          ok = DoubleHandler(this, key, value) ;
        case 'char'
          ok = StringHandler(this, key, value) ;
        case 'cell'
          ok = CellHandler(this, key, value) ;
        otherwise
          error([ upper(class(value)) ' handler not implemented.' ])
       end

    end

    % Polimorfic Get: returns scalars / vectors / matrices of
    % implemente types
    function value = get(this, key)
      assert(ischar(key), 'KEY must be a string.');
      value = GemHandler_('get', this.id_, key) ;
    end

    % Returns datetime scalars / vectors / matrices
    function value = getDate(this, key, type)
      if (nargin < 3) ; type = 'datetime' ; end
      assert(ischar(type), 'TYPE must be a string.');

      value = get(this, key) ;

      switch type
        case 'excel'
          % no need to convert values
        case 'datetime'
          value = datetime(value, 'ConvertFrom', 'excel') ;
        case 'datenum'
          value = datenum(datetime(value, 'ConvertFrom', 'excel')) ;
        otherwise
          error([ upper(type) ' conversion not implemented.' ])
      end

    end

  end

%% Protected Instance Methods
  methods (Access = protected)

    function ok = BoolHandler(this, key, value)
      if (this.ismatrix(value))
        ok = GemHandler_('put', char(NodeType.mbool), this.id_, key, value) ;
      elseif (isvector(value))
        ok = GemHandler_('put', char(NodeType.vbool), this.id_, key, value) ;
      elseif (isscalar(value))
        ok = GemHandler_('put', char(NodeType.bool), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

    function ok = LongHandler(this, key, value)
      if (this.ismatrix(value))
        ok = GemHandler_('put', char(NodeType.mlong), this.id_, key, value) ;
      elseif (isvector(value))
        ok = GemHandler_('put', char(NodeType.vlong), this.id_, key, value) ;
      elseif (isscalar(value))
        ok = GemHandler_('put', char(NodeType.long), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

    function ok = DateHandler(this, key, value)
      value = exceltime(value) ;
      if (this.ismatrix(value))
        ok = GemHandler_('put', char(NodeType.mlong), this.id_, key, value) ;
      elseif (isvector(value))
        ok = GemHandler_('put', char(NodeType.vlong), this.id_, key, value) ;
      elseif (isscalar(value))
        ok = GemHandler_('put', char(NodeType.long), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

    function ok = DoubleHandler(this, key, value)
      if (this.ismatrix(value))
        ok = GemHandler_('put', char(NodeType.mdouble), this.id_, key, value) ;
      elseif (isvector(value))
        ok = GemHandler_('put', char(NodeType.vdouble), this.id_, key, value) ;
      elseif (isscalar(value))
        ok = GemHandler_('put', char(NodeType.double), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

    function ok = StringHandler(this, key, value)
      if (isvector(value))
        ok = GemHandler_('put', char(NodeType.string), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

    function ok = CellHandler(this, key, value)
      if (iscellstr(value))
        ok = GemHandler_('put', char(NodeType.vstring), this.id_, key, value) ;
      else
        this.IS_notyet()
      end
    end

  end

%% Private Static Methods
  methods (Access = private, Static)
    function tf = ismatrix(value)
      tf = ismatrix(value) && ndims(value) == 2 && all(size(value) > 1) ;
    end
    function this.IS_notyet()
      error('IS* statement not implemented.')
    end
  end

%% Private Instance Properties
  properties (Access = private)
    id_ % ID of the Session object instance
  end

end
