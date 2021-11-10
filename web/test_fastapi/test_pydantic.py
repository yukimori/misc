from datetime import datetime
from typing import List, Optional
from pydantic import BaseModel


class User(BaseModel):
    id: int
    name = 'John Doe'
    signup_ts: Optional[datetime] = None
    friends: List[int] = []


# 'not_user_data': "this is not user data"はUserクラスに存在しない -> user作成時には無視される
external_data = {
    'id': '123',
    'signup_ts': '2019-06-01 12:22',
    'friends': [1, 2, '3'],
    'not_user_data': "this is not user data"
}
user = User(**external_data)
print(user.id)
# > 123
print(repr(user.signup_ts))
# > datetime.datetime(2019, 6, 1, 12, 22)
print(user.friends)
# > [1, 2, 3]
print(user.dict())
