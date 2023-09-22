#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <random>


using std::string;
using std::string_view;


class CaesarCipher
{

private:


	string alphabet{ "abcdefghijklmnopqrstuvwxyz" };


	int get_alphabet_index( int iterator, bool decrypt = false )
	{
		return ( ( decrypt ? iterator + alphabet.size() - this->key : iterator + this->key ) % alphabet.size());
	}


	int generate_key( int key )
	{
		auto random_key{ [&] () -> int
		{
			std::random_device random_device{};
			std::mt19937 rng( random_device() );
			std::uniform_int_distribution <> distribution( 1, alphabet.size() - 1 );

			return distribution( rng );
		} };

		if ( this->key != 0 )
		{
			return this->key;
		}

		if ( key < 0 )
		{
			return this->key = random_key();
		}

		this->key = ( ( key == -1 ? random_key() : key % alphabet.size() ) );
		this->key = ( this->key == 0 ? 1 : this->key );

		return this->key = ( this->key == alphabet.size() ? alphabet.size() - 1 : this->key );
	}


protected:


	int key{};
	string data{};


public:


	string_view encrypt( string& data )
	{
		for ( int i = 0; i < data.size(); i++ )
		{
			for ( int j = 0; j < alphabet.size(); j++ )
			{
				if ( data.at( i ) == ( isupper( data.at( i ) ) ? std::toupper( alphabet.at( j ) ) : alphabet.at( j )) )
				{
					data.at( i ) = 
						( isupper( data.at( i ) ) 
							? std::toupper( alphabet.at( get_alphabet_index( j ) ) )
							: alphabet.at( get_alphabet_index( j ) ) 
						);

					break;
				}
			}
		}

		return this->data = data;
	}


	string_view decrypt( string& data )
	{
		for ( int i = 0; i < data.size(); i++ )
		{
			for ( int j = 0; j < alphabet.size(); j++ )
			{
				if ( data.at( i ) == ( isupper( data.at( i ) ) ? std::toupper( alphabet.at( j ) ) : alphabet.at( j ) ) )
				{
					data.at( i ) =
						( isupper( data.at( i ) )
							? std::toupper( alphabet.at( get_alphabet_index( j, true ) ) )
							: alphabet.at( get_alphabet_index( j, true ) )
						);

					break;
				}
			}
		}

		return this->data = data;
	}


	string& get()
	{
		return this->data;
	}


	CaesarCipher( const char* data = nullptr, int key = -1 )
	{
		generate_key( key );

		if ( data != nullptr )
		{
			this->data = string( data );
			encrypt( this->data );
		}
	}
};


int main()
{
	auto cipher = new CaesarCipher( "Julius Caesar" );
	
	std::cout << cipher->get() << std::endl;
	std::cout << cipher->decrypt( cipher->get() );

	getchar();
}
