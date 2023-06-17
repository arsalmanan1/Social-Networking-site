#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Helper
{
public:

	static int StringLength(const char* str)
	{
		int i = 0;
		while (str[i] != '\0')
		{
			i++;
		}
		return i;
	}
	static void StringCopy(char* dest, char* src) {
		int k = 0;
		while (src[k] != '\0')
		{
			dest[k] = src[k];
			k++;
		}
		dest[k] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		int size = StringLength(str);
		char* str2 = new char[size + 1];
		StringCopy(str2, str);
		return str2;
	}
	static int CompareString(const char* cstring1, const char* cstring2)
	{
		int size1 = StringLength(cstring1);
		int size2 = StringLength(cstring2);
		int endsize = 0;
		int flag = 1;
		if (size1 == size2)
		{
			for (int i = 0; (i < size2) && flag == 1; i++)
			{
				if (cstring1[i] != cstring2[i])
				{
					flag = 0;
				}
			}
		}
		else
		{
			flag = 0;
		}




		return flag;
	}
};

class posts;
class object
{
protected:
	char* ID;
	char* name;
public:
	object()
	{
		ID = 0;
		name = 0;
	}
	~object()
	{
		delete[] ID;
		delete[] name;
	}
	char* getID()
	{
		return ID;
	}
	virtual void addpostotimeline(posts*)
	{
	}
	virtual void viewtimeline()
	{

	}
	virtual char* getname()
	{
		return name;
	}
};

class Date
{
	friend ostream& operator<<(ostream&, const Date&);// overloaded stream insertion operator
private:
	int day;
	int month;
	int year;
	static Date currentdate;
public:
	Date()
	{
		day = month = year = 0;
	}
	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	void setdate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	int getday()
	{
		return day;
	}
	int getmonth()
	{
		return month;
	}
	int getyear()
	{
		return year;
	}
	static void setcurrentDate(int d, int m, int y)
	{
		currentdate.day = d;
		currentdate.month = m;
		currentdate.year = y;
	}
	static Date getcurrentDate()
	{
		return currentdate;
	}
	static Date getyesterdayDate()
	{
		return (Date(currentdate.day - 1, currentdate.month, currentdate.year));
	}
	bool CompareDate(Date d2)
	{
		if ((day == d2.day) && (month == d2.month) && (year == d2.year))
		{
			return 1;
		}
		else
			return 0;
	}
	bool ismemory()
	{
		if ((day == currentdate.day) && (month == currentdate.month) && (year != currentdate.year))
		{
			return 1;
		}
		else
			return 0;
	}
	~Date()
	{}
	Date& operator=(const Date& other)
	{
		if (this == &other) {
			// self-assignment, do nothing
			return *this;
		}

		// copy the values of the other Date object's attributes
		day = other.day;
		month = other.month;
		year = other.year;

		return *this;
	}
};
Date Date::currentdate(0, 0, 0);
ostream& operator<<(ostream& out, const Date& obj)
{
	out << obj.day << " / " << obj.month << " / " << obj.year << endl;		//Can we read/write private data in this function?
	return out;
}



class activity {
private:
	int type;
	char* value;
public:
	activity() {
		type = 0;
		value = nullptr;
	}
	~activity() {
		delete[] value;
	}
	void settype(int t) {
		type = t;
	}
	const char* gettype(int t) {
		const char* temp = nullptr;
		if (t == 1) {
			temp = "feeling";
		}
		else if (t == 2) {
			temp = "thinking about";
		}
		else if (t == 3) {
			temp = "making";
		}
		else if (t == 4) {
			temp = "celebrating";
		}
		return temp;
	}
	void readData2(int t, char* temptr) {
		type = t;
		value = Helper::GetStringFromBuffer(temptr);
	}
	void print() {
		cout << gettype(type) << " " << value << endl;
	}
};

class comment {
private:
	char* commentID;
	char* text;
	object* commentby;
	static int totalcomments;
public:
	comment() {
		commentID = nullptr;
		text = nullptr;
		commentby = nullptr;
	}
	comment* makecomment(const char* textofCom, const char* commID, object* poster) {
		comment* comm = new comment();
		comm->text = new char[Helper::StringLength(textofCom) + 1];
		comm->commentID = new char[Helper::StringLength(commID) + 1];
		memcpy(comm->text, textofCom, strlen(textofCom) + 1);
		memcpy(comm->commentID, commID, strlen(commID) + 1);
		comm->commentby = poster;
		return comm;
	}
	~comment() {
		delete[] commentID;
		delete[] text;
		commentby = nullptr;
	}
	void setID(char* temp) {
		commentID = Helper::GetStringFromBuffer(temp);
	}
	void settext(char* temp) {
		text = Helper::GetStringFromBuffer(temp);
	}
	void setcommenter(object* t) {
		delete commentby;
		commentby = t;
	}
	void printtext() {
		cout << "\t" << commentby->getname() << " wrote: '" << text << "'\n";
	}
};
int comment::totalcomments = 0;


class posts
{
private:
	int activitybool;
	char* postID;
	Date datedshared;
	activity* activitii;
	char* text;
	object* sharedby;
	object** likedby;
	comment** comments;
	int likes;
	int noofcomments;
	static int totalposts;
public:
	posts()
	{
		activitybool = 0;
		postID = 0;
		activitii = 0;
		text = 0;
		sharedby = 0;
		likedby = new object * [10];
		for (int i = 0; i < 10; i++)
		{
			likedby[i] = 0;
		}
		likes = 0;
		comments = new comment * [10];
		for (int i = 0; i < 10; i++)
		{
			comments[i] = 0;
		}

		likes = 0;
		noofcomments = 0;
	}
	~posts()
	{
		delete[] postID;
		delete[] text;

		if (likedby)
		{
			delete[] likedby;
		}
		sharedby = nullptr;
		for (int i = 0; i < noofcomments; i++)
		{
			delete comments[i];
		}
		delete[] comments;
		delete activitii;

	}
	static void settotalposts(int t)
	{
		totalposts = t;
	}
	void readData1(ifstream& myfile)
	{
		myfile >> activitybool;
		char temp[100];
		char* temptr = temp;
		myfile >> temptr;
		postID = Helper::GetStringFromBuffer(temptr);
		int d, m, y;
		myfile >> d;
		myfile >> m;
		myfile >> y;
		datedshared.setdate(d, m, y);
		myfile.ignore();
		myfile.getline(temptr, 100);
		text = Helper::GetStringFromBuffer(temptr);
		if (activitybool == 2)
		{
			myfile >> d;
			myfile.getline(temptr, 100);
			activitii = new activity;
			activitii->readData2(d, temptr);
		}


	}
	void setsharedby(object* t)
	{
		sharedby = t;
	}
	void addlike(object* t)
	{
		if (likes < 10)
		{
			// Create a new array with size likes+1
			object** newLikedBy = new object * [likes + 1];

			// Copy the existing likedby array into the new array
			for (int i = 0; i < likes; i++) {
				newLikedBy[i] = likedby[i];
			}

			// Add the new object pointer to the end of the new array
			newLikedBy[likes] = t;

			// Increment the likes counter and delete the old likedby array
			likes++;
			delete[] likedby;

			// Set likedby to point to the new array
			likedby = newLikedBy;
		}
		else
			cout << "REACHED LIKE LIMIT i.e 10" << endl;
	}
	static int gettotalposts()
	{
		return totalposts;
	}
	char* getpostID()
	{
		return postID;
	}
	void addcomment(comment* t)
	{
		if (noofcomments < 10)
		{
			// Create a new array with size likes+1
			comment** newcomm = new comment * [noofcomments + 1];

			// Copy the existing likedby array into the new array
			for (int i = 0; i < noofcomments; i++) {
				newcomm[i] = comments[i];
			}

			// Add the new object pointer to the end of the new array
			newcomm[noofcomments] = t;

			// Increment the likes counter and delete the old likedby array
			noofcomments++;
			delete[] comments;

			// Set likedby to point to the new array
			comments = newcomm;

			//cout << "NEW COMMENT ADDED!\n";
		}
		else
			cout << "reached limit of 10 comments\n";

	}
	Date getsharedDate()
	{
		return datedshared;
	}
	object* getsharedby()
	{
		return sharedby;
	}
	void viewtimeline()
	{
		Date yesterday = Date::getyesterdayDate();
		Date today = Date::getcurrentDate();
		if (datedshared.CompareDate(yesterday) || datedshared.CompareDate(today))
		{
			//cout << postID << endl;

			if (activitybool == 2)
			{
				activitii->print();
			}
			cout << text << endl;
			cout << datedshared << endl;

			for (int i = 0; i < noofcomments; i++)
			{

				comments[i]->printtext();
			}
		}

	}
	void viewpost()
	{
		cout << sharedby->getname() << " shared\n ";
		if (activitybool == 2)
		{
			activitii->print();
		}
		cout << text << endl;
		cout << datedshared << endl;

		for (int i = 0; i < noofcomments; i++)
		{

			comments[i]->printtext();
		}
	}
	void viewLikedlist(const char* temp)
	{
		if (Helper::CompareString(postID, temp))
		{
			cout << temp << " is liked by:\n";
			for (int i = 0; i < likes; i++)
			{
				cout << likedby[i]->getID() << " - " << likedby[i]->getname() << endl;
			}
		}
	}
	void settext(const char* temp)
	{
		text = new char[Helper::StringLength(temp) + 1];
		memcpy(text, temp, strlen(temp) + 1);
	}
	void addnewcomment(comment* t)
	{
		this->viewpost();
		this->addcomment(t);
		cout << "\n\n====NEW COMMENT ADDED!\n\n";
		this->viewpost();
	}
	void setshareddate(Date new_date)
	{
		datedshared = new_date;
	}

};
int posts::totalposts = 0;

class memory : public posts
{
private:
	posts* org_post;
public:
	memory()
	{
		org_post = nullptr;
	}
	~memory()
	{
		delete org_post;
	}
	void sharememory(const char* text, object* user, posts* ptr)
	{
		org_post = ptr;
		settext(text);
		setsharedby(user);
		setshareddate(Date::getcurrentDate());
		
	}
	void print()
	{
		viewpost();
		org_post->viewpost();
	}
};


class Page : public object
{
private:

	char* Title;
	static int totalpages;
	posts** timeline;
	int postcounter;

public:
	Page()
	{
		ID = 0;
		Title = 0;
		timeline = new posts * [10];
		postcounter = 0;
	}
	Page(const Page& rhs)
	{
		ID = Helper::GetStringFromBuffer(rhs.ID);
		Title = Helper::GetStringFromBuffer(rhs.Title);
		timeline = 0;
	}
	~Page()
	{
		/*if(ID)
			delete[] ID;*/
		if(Title)
			delete[] Title;
		if (timeline)
		{
			/*for (int i = 0; i < postcounter; i++)
			{
				if (timeline[i])
					delete timeline[i];
			}*/
			delete[] timeline;
		}
	}
	static int gettotalpages()
	{
		return totalpages;
	}
	static void settotalpages(int p)
	{
		totalpages = p;
	}
	void readData(ifstream& myfile)
	{
		char temp[80];
		char* temptr = temp;
		myfile >> temptr;
		ID = Helper::GetStringFromBuffer(temptr);
		myfile.ignore();
		myfile.getline(temptr, 80);
		Title = Helper::GetStringFromBuffer(temptr);
	}
	void output()
	{
		cout << ID << "\t" << Title << endl;
	}
	static void printlistview(Page** pagelist)
	{
		for (int i = 0; i < totalpages; i++)
		{
			pagelist[i]->output();
		}
	}
	char* getID()
	{
		return this->ID;
	}
	char* gettitle()
	{
		return this->Title;
	}
	void addpostotimeline(posts* t)
	{

		/*timeline = new posts*;*/
		timeline[postcounter] = new posts;

		timeline[postcounter] = t;
		postcounter++;
	}
	char* getname()
	{
		return Title;
	}
	void viewtimeline()
	{
		for (int i = 0; i < postcounter; i++)
		{
			if (timeline[i])
			{
				Date yesterday = Date::getyesterdayDate();
				Date today = Date::getcurrentDate();

				if (timeline[i]->getsharedDate().CompareDate(yesterday) || timeline[i]->getsharedDate().CompareDate(today))
				{

					cout << Title << " is: \n\n";
					cout << endl;
					timeline[i]->viewtimeline();
					cout << endl;
					cout << "===========================================\n";

				}
			}
		}
	}
	void viewcompletetimline()
	{
		for (int i = 0; i < postcounter; i++)
		{
			timeline[i]->viewpost();
			cout << endl << endl;
		}
	}
};
int Page::totalpages = 0;



class users : public object
{
private:
	//char* userID; 
	char* Fname;
	char* Lname;
	Page** pageliked;
	users** friends;
	static int totalusers;
	int numoflikedpages;
	int numoffriends;
	posts** timeline;
	int postcounter;

public:
	users()
	{
		ID = 0;
		Fname = 0;
		Lname = 0;
		pageliked = new Page * [10];
		for (int i = 0; i < 10; i++)
		{
			pageliked[i] = 0;
		}
		//pageliked = 0;
		friends = new users * [10];
		for (int i = 0; i < 10; i++)
		{
			friends[i] = 0;
		}
		numoffriends = 0;
		numoflikedpages = 0;
		timeline = new posts * [10];
		for (int i = 0; i < 10; i++)
		{
			timeline[i] = 0;
		}

	}
	~users()
	{
		
		if (Fname)
			delete[] Fname;
		if (Lname)
			delete[] Lname;

		if (pageliked)
			delete[] pageliked;

		if (friends)
			delete[] friends;

		if (timeline)
			delete[] timeline;
		
			
	}
	users(const users& other) {
		ID = Helper::GetStringFromBuffer(other.ID);
		Fname = Helper::GetStringFromBuffer(other.Fname);
		Lname = Helper::GetStringFromBuffer(other.Lname);
		pageliked = new Page * [10];
		for (int i = 0; i < other.numoflikedpages; i++) {
			pageliked[i] = new Page(*(other.pageliked[i]));
		}
		friends = new users * [10]();
		for (int i = 0; i < other.numoffriends; i++) {
			friends[i] = new users(*(other.friends[i]));
		}
		numoflikedpages = other.numoflikedpages;
		numoffriends = other.numoffriends;
	}
	users& operator=(const users& other) {
		if (this != &other)
		{
			delete[] ID;
			delete[] Fname;
			delete[] Lname;
			for (int i = 0; i < numoflikedpages; i++) {
				delete pageliked[i];
			}
			delete[] pageliked;
			delete[] friends;

			ID = Helper::GetStringFromBuffer(other.ID);
			Fname = Helper::GetStringFromBuffer(other.Fname);
			Lname = Helper::GetStringFromBuffer(other.Lname);
			pageliked = new Page * [10];
			for (int i = 0; i < other.numoflikedpages; i++) {
				//pageliked[i] = new Page(*(other.pageliked[i]));
				pageliked[i] = other.pageliked[i];
			}
			friends = new users * [10];
			for (int i = 0; i < other.numoffriends; i++) {
				//friends[i] = new users(*(other.friends[i]));
				friends[i] = other.friends[i];
			}
			numoflikedpages = other.numoflikedpages;
			numoffriends = other.numoffriends;
		}
		return *this;
	}
	static int gettotalusers()
	{
		return totalusers;
	}
	static void settotalusers(int u)
	{
		totalusers = u;
	}
	void readData(ifstream& myfile)
	{
		char temp[80];
		char* temptr = temp;
		myfile >> temptr;
		ID = Helper::GetStringFromBuffer(temptr);
		myfile >> temptr;
		Fname = Helper::GetStringFromBuffer(temptr);
		myfile >> temptr;
		Lname = Helper::GetStringFromBuffer(temptr);
	}
	void likedpage(Page* liked)
	{
		pageliked[numoflikedpages] = liked;
		numoflikedpages++;
	}
	int getNumoffriends()
	{
		return numoffriends;
	}
	char* getID()
	{
		return ID;
	}
	char* getname()
	{
		return Fname;
	}
	char* getFname()
	{
		return Fname;
	}
	char* getLname()
	{
		return Lname;
	}
	void AddFriend(users* userptr)
	{
		friends[numoffriends] = userptr;
		numoffriends++;
	}
	void viewfriendlist()
	{

		for (int i = 0; i < numoffriends; i++)
		{
			cout << friends[i]->getID() << " " << friends[i]->getFname() << endl;;
		}
		cout << endl << endl;
	}
	void viewlikedpagelist()
	{
		for (int i = 0; i < numoflikedpages; i++)
		{
			cout << pageliked[i]->getID() << " " << pageliked[i]->gettitle() << endl;
		}
		cout << endl;
	}
	void addpostotimeline(posts* t)
	{
		/*timeline = new posts*;*/
		timeline[postcounter] = new posts;

		timeline[postcounter] = t;
		postcounter++;
	}
	void viewcompletetimeline()
	{
		for (int i = 0; i < postcounter; i++)
		{
			if (timeline[i])
			{

				cout << "\t" << Fname << " " << Lname << " is: \n";
				cout << endl;
				timeline[i]->viewpost();
				cout << endl;
				cout << "----------------------------------\n";

			}
		}
	}
	void viewtimeline()
	{
		for (int i = 0; i < postcounter; i++)
		{
			if (timeline[i])
			{
				Date yesterday = Date::getyesterdayDate();
				Date today = Date::getcurrentDate();

				if (timeline[i]->getsharedDate().CompareDate(yesterday) || timeline[i]->getsharedDate().CompareDate(today))
				{

					cout << "\t" << Fname << " " << Lname << " is: \n";
					cout << endl;
					timeline[i]->viewtimeline();
					cout << endl;
					cout << "-----------------------------------\n";
				}
			}
		}
	}
	void viewHomePage()
	{
		for (int i = 0; i < numoffriends; i++)
		{
			friends[i]->viewtimeline();
		}
		for (int i = 0; i < numoflikedpages; i++)
		{
			pageliked[i]->viewtimeline();
		}
	}
	void LikedaPost(posts* ptr)
	{
		ptr->addlike(this);
		cout << "\t\tsuccessfully liked!\n";
	}
	void seeyourmemories()
	{
		for (int i = 0; i < postcounter; i++)
		{
			if ((timeline[i]->getsharedDate()).ismemory())
			{
				cout << "\nWe hope you enjoy looking backand sharing your memories on Facebook, from the most recent to those long ago.\n on this day \n 2 years ago\n\n";
				timeline[i]->viewpost();
			}
		}
	}
	void sharememory(const char* postid , const char* text)
	{
		for (int i = 0; i < postcounter; i++)
		{
			if (Helper::CompareString(postid, timeline[i]->getpostID()))
			{
				memory* mem =  new memory();
				mem->sharememory(text, this , timeline[i]);
				mem->print();
				break;
			}
			
		}
	}

};
int users::totalusers = 0;



class network
{
private:

	Page** pagelist;
	users** userlist;
	posts** postlist;
	static int totalusers;
	static int totalposts;
	static int totalpages;

public:
	network()
	{
		pagelist = nullptr;
		userlist = nullptr;
		postlist = nullptr;
	}
	~network()
	{
		if (pagelist)
		{
			for (int i = 0; i < totalpages; i++)
				if(pagelist[i])
					delete pagelist[i];
			delete[] pagelist;
		}
		
		if (userlist)
		{
			for (int i = 0; i < totalusers; i++)
				if(userlist[i])
					delete userlist[i];
			delete[] userlist;
		}
		if (postlist)
		{
			for (int i = 0; i < totalposts; i++)
				delete postlist[i];
			delete[] postlist;
		}
		
	}
	void load();
	void loadpages();
	void loadusers();
	void loadposts();
	void loadcomments();
	Page* searchpagebyID(const char*);
	users* searchuserbyID(const char*);
	object* searchbyID(char*);
	posts* searchpostbyID(const char*);
	void viewLikedList(const char*);
	void LikeaPost(const char*, users*);
	void viewpost(const char*);
	void addcomments(const char*, const char*, users* user);
	void viewFriends(const char*);
	void viewpage(const char*);
	void FUNCTIONALITY(users*);
	

};
void network::loadpages()
{
	ifstream myfile;
	myfile.open("pages.txt");

	myfile >> totalpages;
	Page::settotalpages(totalpages);
	pagelist = new Page * [totalpages];
	for (int i = 0; i < totalpages; i++)
	{
		pagelist[i] = new Page;
		pagelist[i]->readData(myfile);
	}

	myfile.close();

}
void network::loadusers()
{
	ifstream userfile;
	userfile.open("users.txt");

	userfile >> totalusers;
	users::settotalusers(totalusers);
	userlist = new users * [totalusers];
	char*** temp_Friendlist = new char** [totalusers];
	for (int i = 0; i < totalusers; i++)
	{
		temp_Friendlist[i] = new char* [10];
		for (int j = 0; j < 10; j++)
		{
			temp_Friendlist[i][j] = 0;
		}
	} //allocating space of 10 friends name for each user and initialising to zero

	for (int i = 0; i < totalusers; i++)
	{

		userlist[i] = new users;
		userlist[i]->readData(userfile);

		char* tempptr = new char[3];
		int k = 0;

		//reading friends
		userfile >> tempptr;
		while ((Helper::CompareString(tempptr, "-1")) != 1)
		{
			temp_Friendlist[i][k] = new char[Helper::StringLength(tempptr) + 1];
			Helper::StringCopy(temp_Friendlist[i][k], tempptr);
			k++;
			userfile >> tempptr;
		}

		//reading liked pages
		userfile >> tempptr;
		while ((Helper::CompareString(tempptr, "-1")) != 1)
		{
			Page* liked = searchpagebyID(tempptr);
			if (liked)
			{
				userlist[i]->likedpage(liked);
			}
			userfile >> tempptr;

		}


		/*if (tempptr != nullptr) {
			delete[] tempptr;
		}*/



	}


	//associating the friends
	for (int i = 0; i < totalusers; i++)
	{
		int userr = 0;

		while (temp_Friendlist[i][userr])
		{
			users* userptr = searchuserbyID(temp_Friendlist[i][userr]);
			userlist[i]->AddFriend(userptr);
			userr++;

		}
	}
	userfile.close();


	//deallocation
	for (int i = 0; i < totalusers; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (temp_Friendlist[i][j])
				delete[] temp_Friendlist[i][j];
		}
	}
	delete[] temp_Friendlist;


}
void network::loadposts()
{
	ifstream myfile;
	myfile.open("posts.txt");

	myfile >> totalposts;
	posts::settotalposts(totalposts);
	postlist = new posts * [totalposts];
	for (int i = 0; i < totalposts; i++)
	{
		postlist[i] = new posts;
		postlist[i]->readData1(myfile);
		char temp[80];
		char* temptr = temp;

		myfile >> temptr;
		object* tempobj = searchbyID(temptr);
		postlist[i]->setsharedby(tempobj);
		tempobj->addpostotimeline(postlist[i]);
		myfile >> temptr;
		while (Helper::CompareString(temptr, "-1") != 1)
		{
			object* tempobj1 = searchbyID(temptr);
			if (tempobj1 != nullptr)
			{
				postlist[i]->addlike(tempobj1);
			}
			myfile >> temptr;
		}


	}
	myfile.close();
}
void network::loadcomments()
{
	ifstream myfile;
	myfile.open("comments.txt");
	int totalcomment;
	myfile >> totalcomment;

	for (int i = 0; i < totalcomment; i++)
	{
		comment* coments = new comment;
		char temp[80];
		char* temptr = temp;
		myfile >> temptr;
		char* ID = Helper::GetStringFromBuffer(temptr);
		coments->setID(ID);
		myfile >> temptr;
		posts* postptr = searchpostbyID(Helper::GetStringFromBuffer(temptr));
		postptr->addcomment(coments);
		myfile >> temptr;
		object* comenter = searchbyID(Helper::GetStringFromBuffer(temptr));
		coments->setcommenter(comenter);
		myfile.getline(temptr, 80);
		coments->settext(Helper::GetStringFromBuffer(temptr));




	}
	myfile.close();
}
void network::load()
{
	loadpages();
	loadusers();
	loadposts();
	loadcomments();
}
Page* network::searchpagebyID(const char* temp)
{
	int totalpage = Page::gettotalpages();
	int flag = 0;
	int num = 0;

	for (int i = 0; i < totalpage && flag != 1; i++)
	{
		if (Helper::CompareString(temp, pagelist[i]->getID()))
		{
			flag = 1;
			num = i;

		}
	}

	if (flag == 1)
		return pagelist[num];
	else
		return 0;

}
users* network::searchuserbyID(const char* temp)
{
	int totalusers = users::gettotalusers();
	int flag = 0;
	int num = 0;

	for (int i = 0; i < totalusers && flag != 1; i++)
	{
		if (Helper::CompareString(temp, userlist[i]->getID()) == 1)
		{
			flag = 1;
			num = i;

		}
	}
	if (flag == 1)
		return userlist[num];
	else
		return 0;
}
posts* network::searchpostbyID(const char* temp)
{
	int totalpost = posts::gettotalposts();
	int flag = 0;
	int num = 0;

	for (int i = 0; i < totalpost && flag != 1; i++)
	{
		if (Helper::CompareString(temp, postlist[i]->getpostID()))
		{
			flag = 1;
			num = i;

		}
	}

	if (flag == 1)
		return postlist[num];
	else
		return 0;

}
void network::viewLikedList(const char* temp)
{

	cout << "\n===========================================\n";
	cout << "\n\t command view likelist (" << temp << ")\n\n";
	cout << "===========================================\n";
	int totalposts = posts::gettotalposts();
	for (int i = 0; i < totalposts; i++)
	{
		postlist[i]->viewLikedlist(temp);
	}

}
void network::LikeaPost(const char* temp, users* user)
{
	posts* ptr = searchpostbyID(temp);
	cout << "\n===========================================\n";
	cout << "\n \tcommand like(" << temp << ")\n\n";
	cout << "===========================================\n";
	user->LikedaPost(ptr);

}
void network::viewpost(const char* temp)
{
	posts* ptr = searchpostbyID(temp);
	cout << "\n===========================================\n";
	cout << "\n\t command view " << temp << "\n\n";
	cout << "===========================================\n";
	ptr->viewpost();
}
object* network::searchbyID(char* temp)
{
	object* tempobject;

	tempobject = searchuserbyID(temp);
	if (tempobject != 0)
	{
		return tempobject;
	}
	else
	{
		tempobject = searchpagebyID(temp);
		if (tempobject != 0)
		{
			return tempobject;
		}
		else
		{
			return 0;
		}


	}
}
void network::addcomments(const char* postid, const char* text, users* user)
{
	posts* ptr = searchpostbyID(postid);
	cout << "\n===========================================\n";
	cout << "\n \tcommand: add comment on " << postid << "\n\n";
	cout << "===========================================\n";
	comment* newComment = new comment();
	newComment = newComment->makecomment(text, "c13", user);
	ptr->addnewcomment(newComment);



}
void network::viewFriends(const char* temp)
{
	cout << "\n===========================================\n";
	cout << "\n\t command view friend list of " << temp << "\n\n";
	cout << "===========================================\n";
	users* ptr = searchuserbyID(temp);

	ptr->viewfriendlist();
}
void network::viewpage(const char* temp)
{
	cout << "\n===========================================\n";
	cout << "\n\t command view page " << temp << "\n\n";
	cout << "===========================================\n";
	Page* ptr = searchpagebyID(temp);
	ptr->viewcompletetimline();

}
void network::FUNCTIONALITY(users* currentuser)
{
	cout << "system Date:\t\t" << Date::getcurrentDate() << endl << endl;
	cout << "\n\t\t SOCIAL NETWORK AREA \t\n\n";
	cout << currentuser->getFname() << " " << currentuser->getLname() << " successfully set as current user." << endl << endl;

	cout << "\n===========================================\n";
	cout << "\n \tcommand view friendlist \n\n";
	cout << "===========================================\n";
	currentuser->viewfriendlist();

	cout << "\n===========================================\n";
	cout << "\n \tcommand view liked pages \n\n";
	cout << "===========================================\n";
	currentuser->viewlikedpagelist();

	cout << "\n===========================================\n";
	cout << "\n \tcommand Home page \n\n";
	cout << "===========================================\n";
	currentuser->viewHomePage();

	cout << "\n===========================================\n";
	cout << "\n \tcommand view Timeline \n\n";
	cout << "===========================================\n";
	currentuser->viewcompletetimeline();

	viewLikedList("post5");
	LikeaPost("post5", currentuser);
	viewLikedList("post5");
	viewpost("post4");
	addcomments("post5", "goodluck for your result", currentuser);
	viewFriends("u3");
	viewpage("p1");

	cout << "\n===========================================\n";
	cout << "\n \tcommand see memories \n\n";
	cout << "===========================================\n";
	currentuser->seeyourmemories();

	cout << "\n===========================================\n";
	cout << "\n \tcommand share memory\n \tcommand view timeline \n\n";
	cout << "===========================================\n";
	currentuser->sharememory("post10", "Never thought I will be specialist in this fieldů");
	currentuser->viewcompletetimeline();

}
int network::totalpages = 0;
int network::totalusers = 0;
int network::totalposts = 0;

int main()
{
	network fb;
	fb.load();
	users* currentuser = fb.searchuserbyID("u7");
	Date::setcurrentDate(15, 11, 2017);
	fb.FUNCTIONALITY(currentuser);

}
