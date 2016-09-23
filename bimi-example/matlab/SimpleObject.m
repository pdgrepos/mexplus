classdef SimpleObject < handle

  properties (Access = private)
    id
  end

  methods (Access = public, Static = true)
    function out = ClearAll()
      out = mexlib('clear_all') ;
    end
  end

  methods (Access = public)

    % Object constructor: create an object instance and store its session id
    function this = SimpleObject(name)
      assert(ischar(name), [ class(name) ': wrong argument type.' ]) ;
      this.id = mexlib('new', name) ;
    end

    % Object destructor: delete the homologous library object.
    function delete(this)
      mexlib('delete', this.id) ;
    end

     % Add <key,value> pair
    function ok = add(this, key, value)
      ok = mexlib('add', this.id, key, value) ;
    end

    % Get value from key
    function d = query(this, key)
      d = mexlib('query', this.id, key) ;
    end

    % Set underlying std::matrix.
    function ok = SetMatrix(this, value)
      switch class(value)
        case 'double'
          ok = mexlib('set_mtx', this.id, 'd', value) ;
        case 'cell'
          ok = mexlib('set_mtx', this.id, 's', value) ;
        otherwise
          error([ upper(class(value)) ' handler not implemented.' ])
       end
    end

    % Get underlying std::matrix.
    function mtx = GetMatrix(this, mtx_type)
      if ('d' == mtx_type)
        mtx = mexlib('get_mtx', this.id, 'd') ;
      elseif ('s' == mtx_type)
        mtx = mexlib('get_mtx', this.id, 's') ;
      else
        error([ upper(mtx_type) ' is an invalid code.' ])
      end
    end

  end

  properties (Access = public, Dependent = true)
    Name
  end

  methods
    function set.Name(this, name)
      mexlib('set_name', this.id, name) ;
    end
    function name = get.Name(this)
      name = mexlib('get_name', this.id) ;
    end
  end

end
