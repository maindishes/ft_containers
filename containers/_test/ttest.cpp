Resizes the container so that it contains n elements.

If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).

If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.

If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.

Notice that this function changes the actual content of the container by inserting or erasing elements from it.


void resize(size_type n, value_type val = value_type())
{
    if (n <= _size)
    {
        for (size_type i = _size - n; i < _size; i++)
        {
            _allocator.destroy(_data + i);
        }
    }
    else
    {
        this->reserve(n);
        for (size_type i = _size; i < n; i++)
        {
            _allocator.construct(_data + i, val);
        }
    }
    _size = n;
}