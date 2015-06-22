import requests
import unittest

class TestRestApi(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(TestRestApi, self).__init__(*args, **kwargs)
		self.__api_base_url = "http://localhost:8000"
		self.__login_url = "/api/login"
		self.__logout_url = "/api/logout"
		self.__token_url = "/api/token"
		self.__user_url = "/api/user"
		self.__message_url = "/api/message"
		self.__conversation_url = "/api/conversation"

	def test_authentication_fail(self):
		credentials = {"username":"mateobosco123","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		self.assertEqual("ERROR" , json["result"])
		self.assertEqual(1 , json["code"])

	def test_create_user(self):
		user = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=user)
		json = response.json()
		self.assertEqual("OK" , json["result"])
		self.assertEqual("mpalermo" , json["data"]["username"])

	def test_create_user_and_next_login(self):
		user = "{\"username\":\"mateobosco\",\"password\":\"123456\",\"name\":\"Mateo Bosco\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=user)
		json = response.json()
		self.assertEqual("OK" , json["result"])
		self.assertEqual("mateobosco" , json["data"]["username"])

		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertTrue(json["data"]["token"] != "")

	def test_login_and_logout(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()

		self.assertEqual("OK" , json["result"])
		self.assertTrue(json["data"]["token"] != "")
		credentials["token"] = json["data"]["token"]

		r = requests.get(self.__api_base_url + self.__logout_url, headers = credentials)
		json = r.json()
		self.assertEqual("OK" , json["result"])

	def test_validate_token(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		credentials["token"] = json["data"]["token"]
		self.assertTrue(json["data"]["token"] != "")

		r = requests.get(self.__api_base_url + self.__token_url , headers = credentials)
		json = r.json()

		self.assertEqual("OK", json["result"])

	def test_update_profile(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		credentials["token"] = json["data"]["token"]

		modifiedUser = "{\"name\": \"mateo\" , \"online\": true , \"latitud\": 90, \"longitud\":34, \"location\":\"colegiales\"}"
		r = requests.put(self.__api_base_url + self.__user_url, headers = credentials, data=modifiedUser)
		json = r.json()

		self.assertEqual("OK" , json["result"])
		self.assertEqual("mateo" , json["data"]["name"])
		self.assertEqual(True , json["data"]["online"])
		self.assertEqual(90 , json["data"]["latitud"])
		self.assertEqual(34 , json["data"]["longitud"])
		self.assertEqual("colegiales" , json["data"]["location"])

	def test_send_message(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
	 	resp = r.json()
	 	credentials["token"] = resp["data"]["token"]
		secondUser = "{\"username\":\"pepe\",\"password\":\"contrasenia\",\"name\":\"Jose Argento\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=secondUser)

		message = "{ \"emisor\":\"mateobosco\", \"receptor\":\"pepe\", \"body\":\"mensaje para pepe\" } "
		r = requests.post(self.__api_base_url + self.__message_url , headers = credentials, data = message)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertEqual("mateobosco" , json["data"]["emisor"])
		self.assertEqual("pepe", json["data"]["receptor"])
		self.assertEqual("mensaje para pepe" , json["data"]["body"])

	def test_send_diffusion_message(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
	 	resp = r.json()
	 	credentials["token"] = resp["data"]["token"]

		message = "{ \"emisor\":\"mateobosco\", \"receptor\":\"\", \"body\":\"mensaje para todos\" } "
		r = requests.post(self.__api_base_url + self.__message_url , headers = credentials, data = message)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertEqual("mateobosco" , json["data"]["emisor"])
		self.assertEqual("", json["data"]["receptor"])
		self.assertEqual("", json["data"]["id"])
		self.assertEqual("mensaje para todos" , json["data"]["body"])

	def test_get_conversations(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		resp = r.json()
		credentials["token"] = resp["data"]["token"]

		r = requests.get(self.__api_base_url + self.__conversation_url, headers=credentials)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertTrue(json["data"] != [] )

	def test_get_messages(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		resp = r.json()
		credentials["token"] = resp["data"]["token"]

		secondUser = "{\"username\":\"pepe\",\"password\":\"contrasenia\",\"name\":\"Jose Argento\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=secondUser)
		message = "{ \"emisor\":\"mateobosco\", \"receptor\":\"pepe\", \"body\":\"mensaje para pepe\" } "
		r = requests.post(self.__api_base_url + self.__message_url , headers = credentials, data = message)

		params = {"username":"pepe"}
		r = requests.get(self.__api_base_url + self.__message_url, params=params, headers=credentials)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertTrue(json["data"] != [] )
		self.assertTrue(json["data"][0]["emisor"] in ["mateobosco", "pepe"] )

	def test_get_users(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		resp = r.json()
		credentials["token"] = resp["data"]["token"]

		r = requests.get(self.__api_base_url + self.__user_url , headers = credentials)
		json = r.json()

		self.assertEqual("OK", json["result"])
		self.assertTrue(json["data"] != [] )

	def test_get_user(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		resp = r.json()
		credentials["token"] = resp["data"]["token"]

		secondUser = "{\"username\":\"pepe\",\"password\":\"contrasenia\",\"name\":\"Jose Argento\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=secondUser)

		params = {"username":"pepe"}
		r = requests.get(self.__api_base_url + self.__user_url , params=params, headers = credentials)
		json = r.json()

		self.assertEqual("OK", json["result"])
		self.assertTrue(json["data"] != [] )

