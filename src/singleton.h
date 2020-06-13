/*
 * singleton.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class TSingleton
{

public:
	// Singleton herausgeben
	// und wenn noch nicht existent, erstellen
	static T* get();
	// Singleton löschen
	static void del();

protected:
	// Zeiger auf Singleton
	static T *m_pSingleton;

};

// Initialisierung
template <class T>
T* TSingleton<T>::m_pSingleton = 0;

template <class T>
T* TSingleton<T>::get()
{
	if( !m_pSingleton )
	{
		m_pSingleton = new T();
	}
	return m_pSingleton;
}

template <class T>
void TSingleton<T>::del()
{
	if ( m_pSingleton)
	{
		delete(m_pSingleton);
		m_pSingleton = 0;
	}
}

#endif /* SINGLETON_H_ */
