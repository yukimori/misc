pytorch環境にuvicornインストール
uvicorn main:app --reload --host 0.0.0.0 --port 29001

test_pydantic.pyにてpydanticがないというエラー。fastapiと一緒にはいらないのか。
ModuleNotFoundError: No module named 'pydantic'

個別にインストール
10:22:22 2021/11/10$ pip install pydantic
Installing collected packages: pydantic
Successfully installed pydantic-1.8.2

ref:
https://github.com/apryor6/fastapi_example


* openapi.json
  * http://192.168.10.101:29001/openapi.json
  * 