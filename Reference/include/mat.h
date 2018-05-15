#ifndef __mat_h
#define __mat_h

#include "real.h"
#include "ivec.h"
#include "typedef.h"
#include "complex.h"

using namespace oph;

namespace oph
{
	template<typename T> class mat;
	template<typename T> class matElement;

	template<typename T>
	class __declspec(dllexport) mat
	{
		friend matElement<T>;
	public:
		struct Address
		{
			int level;
			void* next;
		};

	private:
		int dim;
		int* size;
		Address* top;

	public:
		mat(int _dim, int* _size) : dim(_dim)
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = _size[i];

			top = new Address;
			top->level = 0;

			init(top);
		}
		mat(int _dimx, int _dimy = 1, int _dimz = 1) : dim(1)
		{
			_dimy > 1 ? dim++ : dim;
			_dimz > 1 ? dim++ : dim;

			size = new int[dim];

			size[0] = _dimx;
			_dimy > 1 ? size[1] = _dimy : size[1];
			_dimz > 1 ? size[2] = _dimz : size[2];

			top = new Address;
			top->level = 0;

			init(top);
		}
		mat(mat<T>& ref) : dim(ref.dim)
		{
			size = new int[dim];
			for (int i = 0; i < dim; i++) size[i] = ref.size[i];

			top = new Address;
			top->level = 0;

			init(top);
		}
		~mat(void)
		{
			release(top);
			delete[] size;
		}

	private:
		void init(Address* cur)
		{
			if (!cur) return;

			if (cur->level == dim - 1) {
				cur->next = new T[size[cur->level]];
				return;
			}
			cur->next = new Address[size[cur->level]];

			for (int i = 0; i != size[cur->level]; i++) {
				(static_cast<Address*>(cur->next) + i)->level = cur->level + 1;
				init(static_cast<Address*>(cur->next) + i);
			}
		}
		void release(Address* cur)
		{
			if (!cur) return;

			for (int i = 0; cur->level < dim - 1 && i < size[cur->level]; i++)
				release(static_cast<Address*>(cur->next) + i);
			delete[] cur->next;
		}

	public:
		inline matElement<T> operator[](const int index) { return matElement<T>(index, 1, static_cast<void*>(top), this); }
	};

	template<typename T>
	class matElement
	{
	private:
		void* data;

		int level;
		mat<T>* matrix;

	public:
		matElement(int idx, int _level = 0, void* _data = nullptr, mat<T>* _matrix = nullptr)
			: level(_level), data(_data), matrix(_matrix)
		{
			if (_level < 1 || idx >= matrix->size[_level - 1]) {
				data = nullptr;
				return;
			}

			if (level == matrix->dim)
				data = static_cast<void*>((static_cast<T*>(static_cast<mat<T>::Address*>(data)->next) + idx));
			else
				data = static_cast<void*>(static_cast<mat<T>::Address*>(static_cast<mat<T>::Address*>(data)->next) + idx);
		}

		matElement(const matElement<T>& ref) : data(ref.data), level(ref.level), matrix(ref.matrix) {}
		~matElement(void) {}

		operator T() {
			if (data) return *static_cast<T*>(data);
			return T(0);
		}

		matElement& operator =(const T& p) {
			if (data) *static_cast<T*>(data) = p;
			return *this;
		}

		matElement operator[] (const int index) {
			if (!data) return 0;
			return matElement(index, level + 1, data, matrix);
		}
	};

	typedef mat<real> MAT;
	typedef mat<real_t> MAT_T;
	typedef mat<int> MAT_INT;
	typedef mat<oph::Complex<real>> MAT_CPLX;
	typedef mat<oph::Complex<real_t>> MAT_CPLX_T;
}

#endif // !__mat_h
