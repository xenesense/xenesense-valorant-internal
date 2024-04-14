#pragma once
template <typename T1, typename T2>
class Pair
{
public:
    Pair() : first(), second() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    T1 first;
    T2 second;
};

template <typename T1, typename T2>
Pair<T1, T2> hack_make_pair(const T1& first, const T2& second)
{
    return Pair<T1, T2>(first, second);
}

template <typename K, typename V>
class Map
{
public:
    Map() : m_data(nullptr), m_size(0) {}

    ~Map()
    {
        if (m_data)
        {
            delete[] m_data;
        }
    }

    void insert(const K& key, const V& value)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_data[i].first == key)
            {
                m_data[i].second = value;
                return;
            }
        }

        Pair<K, V>* newData = new Pair<K, V>[m_size + 1];
        for (size_t i = 0; i < m_size; ++i)
        {
            newData[i] = m_data[i];
        }

        newData[m_size] = hack_make_pair(key, value);
        delete[] m_data;
        m_data = newData;
        ++m_size;
    }

    V& operator[](const K& key)
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_data[i].first == key)
            {
                return m_data[i].second;
            }
        }

        Pair<K, V>* newData = new Pair<K, V>[m_size + 1];
        for (size_t i = 0; i < m_size; ++i)
        {
            newData[i] = m_data[i];
        }

        newData[m_size] = hack_make_pair(key, V());
        delete[] m_data;
        m_data = newData;
        ++m_size;
        return m_data[m_size - 1].second;
    }


    size_t size() const
    {
        return m_size;
    }



    Pair<K, V>* begin()
    {
        return m_data;
    }

    Pair<K, V>* end()
    {
        return m_data + m_size;
    }

private:
    Pair<K, V>* m_data;
    size_t m_size;
};