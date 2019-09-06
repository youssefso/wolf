using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBulletAnimation : MonoBehaviour {

	public GameObject Hiteffect;
	void OnCollisionEnter2D(Collision2D collision)
	{
		if (collision.gameObject.tag != "Enemy")
		{
			GameObject hit = Instantiate(Hiteffect, transform.position, Quaternion.identity);
			Destroy(hit, 1f);
			Destroy(gameObject,0.6f);
		}
		if (collision.gameObject.tag == "Player")
		{
			collision.rigidbody.GetComponent<Playerhealth>().DamagePlayer(10);
		}
		if (collision.gameObject.tag == "Bullet")
		{
			GameObject hit = Instantiate(Hiteffect, transform.position, Quaternion.identity);
			Destroy(hit, 1f);
			Destroy(gameObject);
		}
	}
}
