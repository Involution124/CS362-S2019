import java.io.*;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

import junit.framework.TestCase;
import java.util.Random;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.file.Paths;
import java.util.ArrayList;
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

	static ArrayList<String> schemeList = new ArrayList<>();
	static ArrayList<String> authorityist = new ArrayList<>();
	static ArrayList<String> queryList = new ArrayList<>();
	static ArrayList<String> pathList = new ArrayList<>();

	public RandomTests(String s) {
		super(s);
		Goodurls = new ArrayList<String>();
		Badurls = new ArrayList<String>();
		rand = new Random();
		String[][] possibilities = { validScheme,invalidScheme, validAuthority,invalidAuthority, validPort,invalidPort, validPath,invalidPath, validQuery,invalidQuery };
		int state = 0;
		Random random = new Random();
		String url;
        int randScheme;
        int randAuthority;
        int randomQuery;
        int randomPath;
		UrlValidator UV = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

		for(int i=0; i<50000; i++) {
			boolean isGood = true;
			String url = "";
			for(int id=0; id<10; id+=2) {
				int isInvalid = rand.nextInt(2)*rand.nextInt(2) * rand.nextInt(2);
				if(id == 8) {
					isInvalid = 0;
				}
				if(isInvalid == 1) {
					isGood = false;
				}
				int comp = rand.nextInt(possibilities[id+isInvalid].length);
				url += possibilities[id+isInvalid][comp];
			}
			if(isGood) {
				System.out.println("Valid: " + url);
				Goodurls.add(url);
			} else {
				System.out.println("Invalid: " + url);
				Badurls.add(url);
			}
		}

		// Read Text Document and add to schemeList, authorityList, queryList, pathList
		readURLFile();
		int randomTest = 1;
		// Random Test until all conditions are met
		while (state != 4) {
			StringBuilder sb = new StringBuilder();

			// Get random scheme, authority, and query for URL
			randScheme = random.nextInt(schemeList.size());
			randAuthority = random.nextInt(authorityList.size());
			randomQuery = random.nextInt(queryList.size());
			randomPath = random.nextInt(pathList.size());

			sb.append(schemeList.get(randScheme));
			sb.append(authorityList.get(randAuthority));
			sb.append(pathList.get(randomPath));
			sb.append(queryList.get(randomQuery));
			url = sb.toString();

            System.out.println("Random Test #" + randomTest + " State: " +  state + " URL: " + url);

			if (state == 0 && UV.isValid(url)) {
				state++;
			} else if (state == 1 && !UV.isValid(url)) {
				state++;
			} else if (state == 2 && schemeList.get(randScheme).equals("http://")) {
				state++;
			} else if (state == 3 && schemeList.get(randScheme).equals("https://")) {
				state++;
			}
		}
	}

	public static void readURLFile() {
		try {
            BufferedReader br = new BufferedReader(new FileReader(System.getProperty("user.dir") + "projects/coletyl/URLValidatorInCorrect/test/URLs.txt"));
            StringBuilder sb = new StringBuilder();
			String line = br.readLine();

			// Read each line in text
			while (line != null) {
                URL url = new URL(line);

                if (url.getProtocol() != null) {
                    schemeList.add(url.getProtocol() + "://");
                }

                if (url.getAuthority() != null) {
                    authorityList.add(url.getAuthority());
                }

                if (url.getQuery() != null) {
                    queryList.add("?" + url.getQuery());
                }

                if (url.getPath() != null) {
                    pathList.add(url.getPath());
                }

                line = br.readLine();
            }
		} catch (MalformedURLException e) {
            System.out.println(e);
        } catch (IOException e) {
            e.printStackTrace();
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
