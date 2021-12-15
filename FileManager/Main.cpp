#include <iostream>
#include <list>

//
//Файловый менеджер 
// показывать содержимое дисков;
// создавать папки / файлы;
// удалять папки / файлы;
// переименовывать папки / файлы;
// копировать / переносить папки / файлы;
// вычислять размер папки / файла;


class Folder
{
private:
	std::string _name;

	//вышестоящий элемент
	std::shared_ptr <Folder> _prew;

	std::list <std::shared_ptr <Folder>> _content;

public:
	Folder(std::string name, std::shared_ptr <Folder> prew=nullptr) :_name{ name }, _prew{ prew },_content{nullptr} {}
	Folder() {}
	~Folder() {}

	//name
	//getter
	std::string name() { return _name; };
	//setter
	void name(std::string name) { _name = name; }
	
	//content
	//getter
	std::list <std::shared_ptr <Folder>> content() { return _content; }



	//setter
	void content(std::list <std::shared_ptr <Folder>> content) { _content = content; }

	//prew
	//getter
	std::shared_ptr <Folder> prew() { return _prew; };
	//setter
	void prew (std::shared_ptr <Folder> prew) { _prew = prew; }
	
	//добвление новой папки
	void addContent()
	{
		std::string name;
		std::cout << "Введите имя новой папки: ";
		std::cin >> name;
	
		_content.push_back(std::make_shared <Folder> (name,(std::shared_ptr<Folder>) this));
		if (*_content.rbegin())
			std::cout << "Папка создана\n";
	}
	void addContent(std::shared_ptr <Folder> fold)
	{
		_content.push_back(fold);
		std::cout << "Копирование завершено\n";
	}
	//Переименование папки
	void renameContent()
	{
		std::string name;
		std::cout << "Введите новое имя";
		std::cin >> name;
		std::cout << "\n Имя " << this->name() << "изменено на ";
		this->name(name);
		std::cout << this->name() << std::endl;
	}

	//удаление выбранной папки
	void removeContent(std::shared_ptr <Folder> fold)
	{
			_content.remove(fold);
			std::cout << "Удаление выполнено\n";
	}

	//выбор папки
	std::shared_ptr <Folder> getContain()
	{
			char cIndex;
			int index=0;
			for (int i = 0; i < 5; ++i)
			{
				std::cin >> cIndex;
				index = cIndex - '0' - 1;
				if (index <= _content.size()-1 && index >= 0)
				{
					auto it = _content.begin();
					std::advance(++it, index);
					return *it;
				}
				else
					std::cout << "Некорректное значение поля\n";
			}
		
	}

	/*Копирование  - это пока что самый сложный метод.
	основная сложность - рекурсия, в которой легко потеряться.
	*/

	//Копирование (НАДО ПРОВЕРЯТЬ!!!!)
	std::shared_ptr <Folder> copyFolder()
	{
		std::shared_ptr <Folder> Newfold = std::make_shared <Folder>(this->name());
		
		auto end = this->_content.end();
		for (auto iter = this->_content.begin(); iter != end; ++iter)
		{
			Newfold->_content.push_back((*iter)->copyFolder()); 
		}
		return Newfold;
	}

	//Перемещение
	void replaceContent(std::shared_ptr <Folder> source, std::shared_ptr <Folder> newPlace)
	{
		newPlace->content().push_back(source);
		source.reset();
	}
	void showContent()
	{
	

		std::cout << "\nСодержимое:\n";
		auto iter = _content.begin();
		auto end = _content.end();
		//Проверка на пустоту(нужно проверять)
		if (++iter == end)
		{
			std::cout << "[Пустая папка]\n";
			return;
		}
		//iter = _content.begin()

		//не смог подружить инициализацию индекса и итератора в одном поле
		int i = 1;//для пользователя нагляднее
		for (; iter != end; ++iter,++i)
		{
			std::cout << "[" << i << "]" << " - ";
			std::cout<<(*iter)->name() << std::endl;
		}
	}

	void showPath()
	{
		if (_prew)
			 _prew->showPath();
		std::cout << "//" << name();
		
	}
	void openFolder()
	{
		showPath();
		showContent();
	}
};


class Interface
{
protected:
	std::shared_ptr <Folder> _root;
	std::shared_ptr <Folder> _contain;
	std::shared_ptr <Folder> _buffer;

public:


	char menu(std::shared_ptr <Folder> fold)
	{
		char m;

		do
		{

			std::cout << "Действия:\n";
			//Блок с наполнением
			if (fold->content().size()>1)
			{
				std::cout << "[O] - Открыть\n";
				std::cout << "[R] - Переименовать\n";
				std::cout << "[X] - Переместить\n";
				std::cout << "[C] - Копировать\n";
				std::cout << "[D] - Удалить\n\n";
			}
			//Блок без наполнения
			if (isBuffer())
				std::cout << "[V] - Вставить\n";
			std::cout << "[A] - Создать новую папку\n";
			std::cout << "[N] - Создать новый файл\n";
				if (fold->prew())
			std::cout << "[E] - Назад\n";
			std::cout << "[Q] - Выход из программы\n";
			std::cin >> m;
			std::cin.ignore();


			//Проверяю отдельными блоками для избежанрия дублирования
			

			if (m == 'V' ||
				m == 'A' ||
				m == 'N' ||
				m == 'E' ||
				m == 'Q')
					break;
					
			if (m == 'v' ||
				m == 'a' ||
				m == 'n' ||
				m == 'e' ||
				m == 'q')
			{
				m = std::toupper(m);
				break;
			}
				
			if (fold)
			{
				if (m == 'O' ||
					m == 'R' ||
					m == 'X' ||
					m == 'C' ||
					m == 'D')
						break;
		
				if (m == 'o' ||
					m == 'r' ||
					m == 'x' ||
					m == 'c' ||
					m == 'd')
				{
					m = std::toupper(m);
					break;
				}			
			}
			std::cout << "Некорректное значение меню\n";
		} while (true);
		return m;
	}

	bool isBuffer()
	{
		if (_buffer) return true;
		return false;
	}
		void run(std::shared_ptr <Folder> file)
		{

			char m;
			do
			{
				system("cls");
				std::cout << "Файловый менеджер.\n";

				file->openFolder();
				//на этапе getContain выбираем папку
				if (file->content().size()>1)  //По нпонятной причине метод empty не работает как способ определить наполенение списка
					_contain = file->getContain();
				 
				//в меню выбираем, что с ней делать
				m = menu(_contain);

				switch (m)
				{
					//open
				case 'O':
					std::cout << "open\n";
					file = file->getContain();
					break;
				//rename
				case 'R':
					std::cout << "rename\n";
					_contain->renameContent();
					break;


				//replace
				case 'X':
					_buffer = _contain;
					break;
				//copy
				case 'C':
					std::cout << "copy\n";
					_buffer = _contain->copyFolder();

					break;
				//delete
				case 'D':
					std::cout << "delete\n";
					file->removeContent(_contain);
					break;
				//insert
				case 'V':
					std::cout << "Копирование файла\n";
					file->addContent(_buffer);
					break;
				//add Folder
				case 'A':
					std::cout << "add Folder\n";
					file->addContent();
					break;

				//addFile
				case 'N':
					std::cout << "add file\n";
					std::cout << "not yet\n";
					break;

				//exit to prew
				case 'E':
					std::cout << "exit to prew\n";

					if (file->prew())
						file = file->prew();
					else
						std::cout << "Это корневая папка\n";
					break;
					//exit all
				case 'Q':

					std::cout << "Выход из программы\b";
					break;

				default:
					std::cout << "непредвиденная ошибка в меню\n";
					break;
				}

			} while (m != 'Q');
		}
		
		Interface(std::string name) : _root{ std::make_shared <Folder>(name, nullptr) },

		_contain{_root},_buffer{nullptr}

	{
		run(_root);
	}



	~Interface() {}
};


int main()
{
	setlocale(LC_ALL, "");

	Interface user1("user1");

	return 0;
}