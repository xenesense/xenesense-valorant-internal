#pragma once
#pragma once

namespace hack
{
    template <class _Ty>
    struct remove_reference {
        using type = _Ty;
    };

    template <class _Ty>
    struct remove_reference<_Ty&> {
        using type = _Ty;
    };

    template <class _Ty>
    struct remove_reference<_Ty&&> {
        using type = _Ty;
    };

    template <class _Ty>
    using remove_reference_t = typename remove_reference<_Ty>::type;

    template <class _Ty>
    struct remove_const {
        using type = _Ty;
    };

    template <class _Ty>
    struct remove_const<const _Ty> {
        using type = _Ty;
    };

    template <class _Ty>
    using remove_const_t = typename remove_const<_Ty>::type;
}

namespace hack
{
    template<class _Ty>
    using clean_type = typename hack::remove_const_t<hack::remove_reference_t<_Ty>>;

    template <int _size, char _key1, char _key2, char _key3, char _key4, typename T>
    class hack_crypter
    {
    public:
        __inline constexpr hack_crypter(T* data)
        {
            crypt(data);
        }

        __inline T* get()
        {
            return _storage;
        }

        __inline int size()
        {
            return _size;
        }

        __inline  char key()
        {
            return _key1;
        }

        __inline  T* encrypt()
        {
            if (!isEncrypted())
                crypt(_storage);

            return _storage;
        }

        __inline  T* decrypt()
        {
            if (isEncrypted())
                crypt(_storage);

            return _storage;
        }

        __inline bool isEncrypted()
        {
            return _storage[_size - 1] != 0;
        }

        __inline void clear()
        {
            for (int i = 0; i < _size; i++)
            {
                _storage[i] = 0;
            }
        }

        __inline operator T* ()
        {
            decrypt();

            return _storage;
        }

    private:
        __inline constexpr void crypt(T* data)
        {
            for (int i = 0; i < _size; i++)
            {
                _storage[i] = data[i] ^ (_key1 + i % (1 + _key2) % (2 + _key3) % (3 + _key4));
            }
        }

        T _storage[_size]{};
    };
}

#define encrypt_key(str, key1, key2, key3, key4) []() { \
			constexpr static auto crypted = hack::hack_crypter \
				<sizeof(str) / sizeof(str[0]), key1, key2, key3, key4, hack::clean_type<decltype(str[0])>>((hack::clean_type<decltype(str[0])>*)str); \
					return crypted; }()

#define _(str) encrypt_key(str, __TIME__[4], __TIME__[2], __TIME__[8], __TIME__[5])
