import requests
import unittest

class TestRestApi(unittest.TestCase):
	def __init__(self, *args, **kwargs):
		super(TestRestApi, self).__init__(*args, **kwargs)
		self.__api_base_url = "http://localhost:8000"
		self.__login_url = "/api/login"
		self.__user_url = "/api/user"

	def test_authentication_fail(self):
		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		print json
		self.assertEqual(json["result"],"ERROR")
		self.assertEqual(json["code"], 1)

	def test_create_user(self):
		user = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=user)
		json = response.json()
		print json
		self.assertEqual(json["result"], "OK")
		self.assertEqual(json["data"]["username"], "mpalermo")

	def test_create_user_and_next_login(self):
		user = "{\"username\":\"mateobosco\",\"password\":\"123456\",\"name\":\"Mateo Bosco\"}"
		response = requests.post(self.__api_base_url+self.__user_url, data=user)
		json = response.json()
		print json
		self.assertEqual(json["result"], "OK")
		self.assertEqual(json["data"]["username"], "mateobosco")

		credentials = {"username":"mateobosco","password":"123456"}
		r = requests.get(self.__api_base_url + self.__login_url, headers=credentials)
		json = r.json()
		self.assertEqual(json["result"],"OK")
		self.assertTrue(json["data"]["token"] != "")