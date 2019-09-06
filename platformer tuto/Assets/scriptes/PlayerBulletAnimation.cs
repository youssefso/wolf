using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBulletAnimation : MonoBehaviour {

	public GameObject Hiteffect;
	public int damageAmount = 10;
	void OnCollisionEnter2D(Collision2D collision)
	{
		if (collision.gameObject.tag != "Player")
		{
			GameObject hit = Instantiate(Hiteffect, transform.position, Quaternion.identity);
			Destroy(hit, 1f);
			Destroy(gameObject,0.6f);
		}
		
		if (collision.gameObject.tag == "Enemy")
		{
			collision.gameObject.GetComponent<Enemyhealth>().DamageEnemy(20);
		}
		
		if (collision.gameObject.tag == "Bullet")
		{
			GameObject hit = Instantiate(Hiteffect, transform.position, Quaternion.identity);
			Destroy(hit, 1f);
			Destroy(gameObject);
		}
	}
}
