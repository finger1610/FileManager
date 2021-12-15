#include <iostream>
#include <list>

//
//�������� �������� 
// ���������� ���������� ������;
// ��������� ����� / �����;
// ������� ����� / �����;
// ��������������� ����� / �����;
// ���������� / ���������� ����� / �����;
// ��������� ������ ����� / �����;


class Folder
{
private:
	std::string _name;

	//����������� �������
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
	
	//��������� ����� �����
	void addContent()
	{
		std::string name;
		std::cout << "������� ��� ����� �����: ";
		std::cin >> name;
	
		_content.push_back(std::make_shared <Folder> (name,(std::shared_ptr<Folder>) this));
		if (*_content.rbegin())
			std::cout << "����� �������\n";
	}
	void addContent(std::shared_ptr <Folder> fold)
	{
		_content.push_back(fold);
		std::cout << "����������� ���������\n";
	}
	//�������������� �����
	void renameContent()
	{
		std::string name;
		std::cout << "������� ����� ���";
		std::cin >> name;
		std::cout << "\n ��� " << this->name() << "�������� �� ";
		this->name(name);
		std::cout << this->name() << std::endl;
	}

	//�������� ��������� �����
	void removeContent(std::shared_ptr <Folder> fold)
	{
			_content.remove(fold);
			std::cout << "�������� ���������\n";
	}

	//����� �����
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
					std::cout << "������������ �������� ����\n";
			}
		
	}

	/*�����������  - ��� ���� ��� ����� ������� �����.
	�������� ��������� - ��������, � ������� ����� ����������.
	*/

	//����������� (���� ���������!!!!)
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

	//�����������
	void replaceContent(std::shared_ptr <Folder> source, std::shared_ptr <Folder> newPlace)
	{
		newPlace->content().push_back(source);
		source.reset();
	}
	void showContent()
	{
	

		std::cout << "\n����������:\n";
		auto iter = _content.begin();
		auto end = _content.end();
		//�������� �� �������(����� ���������)
		if (++iter == end)
		{
			std::cout << "[������ �����]\n";
			return;
		}
		//iter = _content.begin()

		//�� ���� ��������� ������������� ������� � ��������� � ����� ����
		int i = 1;//��� ������������ ���������
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

			std::cout << "��������:\n";
			//���� � �����������
			if (fold->content().size()>1)
			{
				std::cout << "[O] - �������\n";
				std::cout << "[R] - �������������\n";
				std::cout << "[X] - �����������\n";
				std::cout << "[C] - ����������\n";
				std::cout << "[D] - �������\n\n";
			}
			//���� ��� ����������
			if (isBuffer())
				std::cout << "[V] - ��������\n";
			std::cout << "[A] - ������� ����� �����\n";
			std::cout << "[N] - ������� ����� ����\n";
				if (fold->prew())
			std::cout << "[E] - �����\n";
			std::cout << "[Q] - ����� �� ���������\n";
			std::cin >> m;
			std::cin.ignore();


			//�������� ���������� ������� ��� ���������� ������������
			

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
			std::cout << "������������ �������� ����\n";
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
				std::cout << "�������� ��������.\n";

				file->openFolder();
				//�� ����� getContain �������� �����
				if (file->content().size()>1)  //�� ��������� ������� ����� empty �� �������� ��� ������ ���������� ����������� ������
					_contain = file->getContain();
				 
				//� ���� ��������, ��� � ��� ������
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
					std::cout << "����������� �����\n";
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
						std::cout << "��� �������� �����\n";
					break;
					//exit all
				case 'Q':

					std::cout << "����� �� ���������\b";
					break;

				default:
					std::cout << "�������������� ������ � ����\n";
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