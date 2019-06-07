
import java.io.File;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import junit.framework.TestCase;
import java.util.Random;




public class UnitTests extends TestCase {
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

	public UnitTests(String s) {
		super(s);
		Goodurls = new ArrayList<String>();
		Badurls = new ArrayList<String>();
		rand = new Random();
		String[][] possibilities = { validScheme,invalidScheme, validAuthority,invalidAuthority, validPort,invalidPort, validPath,invalidPath, validQuery,invalidQuery };
		String[] Scheme = validScheme; 
		String[] Authority = validAuthority; 
		String[] Port = validPort;
		String[] Path = validPath;
		String[] Query = validQuery;
		for(String scheme: Scheme) {
			for(String auth: Authority) {
				for(String port: Port) {
					for(String path: Path){
						for(String query: Query) {
							String url = scheme + auth + port + path + query;
							Goodurls.add(url);
						}
					}
				}
			}
		}
		for(int i=0; i<4; i++) {
			switch(i){
				case 0:
					Scheme = invalidScheme;
					break;
				case 1:
					Scheme = validScheme;
					Authority = invalidAuthority;
					break;
				case 2:
					Authority = validAuthority;
					Port = invalidPort;
					break;
				case 3:
					Port = validPort;
					Path = invalidPath;
					break;
			}
			for(String scheme: Scheme) {
				for(String auth: Authority) {
					for(String port: Port) {
						for(String path: Path){
							for(String query: Query) {
								String url = scheme + auth + port + path + query;
								Badurls.add(url);
								//System.out.println(url);

							}
						}
					}
				}
			}
		}
	
	}

	
	public static void testValidUrls() {
		UrlValidator UV = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		for(String url : Goodurls) {
			if(!UV.isValid(url)) {
				assert(UV.isValid(url));
				System.out.println("Says isnt valid - " + url);
			}
			
		}
	}

	public static void testEdgeCases() {
		UrlValidator UV = new UrlValidator();
		assert(!UV.isValid("http://256.256.256.256"));
		assert(!UV.isValid("http://google.com:65536"));
		assert(!UV.isValid("http://a"));
		assert(!UV.isValid("http:///q?=1"));
		assert(!UV.isValid("//google.com//"));
		assert(!UV.isValid("file://google.com//"));
		assert(!UV.isValid("http://256.256.256.256"));
		assert(!UV.isValid(""));
	}
	
	public static void testInvalidUrls() {
		UrlValidator UV = new UrlValidator();
		for(String url : Badurls) {
			if(UV.isValid(url)) {
				assert(!UV.isValid(url));
				System.out.println("Says Is valid - " + url);
			}
		}
	}
}
