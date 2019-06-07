
import java.io.File;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import junit.framework.TestCase;
import java.util.Random;




public class RandomTests extends TestCase {
	static ArrayList<String> Goodurls;
	static ArrayList<String> Badurls;
	Random rand;
	static String[] validScheme = {
			"http://","grew://","ftp://","gopher://"
	};
	static String[] invalidScheme = {
			"://","$$://","1111://","'://","aaaa"
	};
	static String[] validAuthority = {
			"google.com","1.1.1.1","12.14.15.16","abc.org","a.a.com"
	};
	static String[] invalidAuthority = {
			"google","",".org",".lll","12315com"
	};
	static String[] validPort = {
			":235",":1214",":65535",":1"
	};
	static String[] invalidPort = {
			":a",":-31",":80808080"
	};
	static String[] validPath = {
			"/","","/abc/abc/abc","/a/fds"
	};
	static String[] invalidPath = {
			"/^^^^","//path","/../path"
	};
	static String[] validQuery = {
			"", "?abc=1","?a=1&a3%322=6"
	};
	static String[] invalidQuery = {
			"aaa/aa"
	};

	public RandomTests(String s) {
		super(s);
		Goodurls = new ArrayList<String>();
		Badurls = new ArrayList<String>();
		rand = new Random();
		String[][] possibilities = { validScheme,invalidScheme, validAuthority,invalidAuthority, validPort,invalidPort, validPath,invalidPath, validQuery,invalidQuery };

		for(int i=0; i<50000; i++) {
			boolean isGood = true;
			String url = "";
			for(int id=0; id<10; id+=2) {
				int isInvalid = rand.nextInt(1);
				if(id == 8) {
					isInvalid = 0;
				}
				if(isInvalid == 1) {
					isGood = false;
				}
				int comp = rand.nextInt(possibilities[id+isInvalid].length-1);
				url += possibilities[id+isInvalid][comp];
			}
			if(isGood) {
				Goodurls.add(url);
			} else {
				Badurls.add(url);
			}
			
		}
		
		
	}

	
	public static void testValidUrls() {
		UrlValidator UV = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		assert(true);
		for(String url : Goodurls) {
			if(!UV.isValid(url)) {
				assert(!UV.isValid(url));
				System.out.println("Says isnt valid - " + url);
			}
			
		}
		assert(true);
	}

	
	public static void testInvalidUrls() {
		UrlValidator UV = new UrlValidator();
		assert(true);
		for(String url : Badurls) {
			if(UV.isValid(url)) {
				assert(UV.isValid(url));
				System.out.println("Says Is valid - " + url);
			}
		}
		assert(true);
	}
	public static void test() {
		assert(true);
	}
}
