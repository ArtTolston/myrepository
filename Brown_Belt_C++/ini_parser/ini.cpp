#include"ini.h"
#include<string>
#include<sstream>
namespace Ini {
	Section& Document::AddSection(string name) {
		return sections[name];
	}

	const Section& Document::GetSection(const string& name) const {
		return sections.at(name);
	}

	size_t Document::SectionCount() const {
		cerr << sections.size();
		return sections.size();
	}

	Section Read_Section(istream& input) {
		Section section;
		while(input.peek() != '[' && !input.eof()) {
			string line;
			getline(input, line);
			if (line == string())
				break;
			size_t del = line.find("=");
			cerr << line.substr(0, del) << " : " << line.substr(del + 1, line.size()) << endl;
			section[line.substr(0, del)] = line.substr(del + 1, line.size());
		}
		return section;
	}

	Document Load(istream& input) {
		string line;
		Document dc;
		while (getline(input, line) && line.size() > 0) {
			
			line = line.substr(1, line.size() - 2);
			cerr << "name " << line <<  endl;
			Section section = Read_Section(input);
			dc.AddSection(line) = section;
		}
		return dc;
	}
}