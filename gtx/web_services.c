#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>

int  main(int argc, char **argv)
{

  /* LIB JSON-C PART */
    /* Create a JSON object */
    json_object * jObj = json_object_new_object();

    /* Create a string element */
    json_object *jString = json_object_new_string("Guybrush");

    /* Include the element to the JSON final object */
    json_object_object_add(jObj,"name", jString);


  /* LIB CURL PART */
    /* Initialize CURL */ 
    CURL *curlHandler = curl_easy_init();

    if(curlHandler) {
      /* Set CURL parameters */
      curl_easy_setopt(curlHandler, CURLOPT_URL, "http://api.yoururl.com");
      curl_easy_setopt(curlHandler, CURLOPT_CUSTOMREQUEST, "POST");
      curl_easy_setopt(curlHandler, CURLOPT_POSTFIELDS,  
                json_object_to_json_string(jObj));

      /* Perform the request */ 
      CURLcode res = curl_easy_perform(curlHandler);

      /* Check for errors */ 
      if(res != CURLE_OK)
        fprintf(stderr, "CURL failed: %s\n",
                curl_easy_strerror(res));

      /* Clean up */ 
      curl_easy_cleanup(curlHandler);
      json_object_object_del(jObj, "name");
      free(jObj);
  }
  return 0;
}
