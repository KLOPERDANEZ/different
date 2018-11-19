    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <iterator>
     
    template <class Iter, class Func>
    class Converter;
     
    template <class Iter, class Func>
    class TempIter
    {
    public:
    	typedef TempIter self_type;
    	typedef decltype((*((Func*) (nullptr)))(*((typename Iter::value_type*)(nullptr)))) value_type;
    	typedef value_type& reference;
    	typedef value_type* pointer;
    	typedef std::forward_iterator_tag iterator_category;
    	typedef typename Iter::difference_type difference_type;
     
    	TempIter(Iter obj, Converter<Iter, Func>* converter, const Func& func):
    		obj_(obj),
    		converter_(converter),
    		func_(func)
    	{
    	}
     
    	TempIter& operator++()
    	{
    		++obj_;
    		return *this;
    	}
     
    	const TempIter operator++(int)
    	{
    		TempIter temp(*this);
    		++obj_;
    		return temp;
    	}
     
    	value_type operator*()
    	{
    		return func_(*obj_);
    	}
     
    	bool operator==(const TempIter<Iter, Func> any)
    	{
    		return obj_ == any.obj_;
    	}
     
    	bool operator!=(const TempIter<Iter, Func> any)
    	{
    		return obj_ != any.obj_;
    	}
     
    private:
    	Iter obj_;
    	Converter<Iter, Func>* converter_;
    	const Func& func_;
    };
     
    template <class Iter, class Func>
    class Converter
    {
    	Iter current_;
    	Iter finish_;
    	const Func& func_;
     
    public:
    	Converter(Iter start, Iter finish, const Func& func):
    			current_(start),
    			finish_(finish),
    			func_(func)
    	{
    	}
     
    	TempIter<Iter, Func> begin()
    	{
    		return TempIter<Iter, Func>(current_, this, func_);
    	}
     
    	TempIter<Iter, Func> end()
    	{
    		return TempIter<Iter, Func>(finish_,  this, func_);
    	}
    };
     
     
    int main()
    {
    	std::vector<int> v = {1, 2, 3};
    	auto f = [](auto v) { return v * 3.14; };
    	Converter<decltype(std::begin(v)), decltype(f)> conv(v.begin(), v.end(), f);
    	std::vector<double> v2(conv.begin(), conv.end());
    	std::copy(std::begin(v2), std::end(v2), std::ostream_iterator<double>(std::cout, " "));
    }
