using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyWeaponController : MonoBehaviour {

	// Use this for initialization
	public GameObject enemyBullet;
	public Transform firePosition;
	public float shootforce;
	public float firerate;
	float fire;
	void Start () {
		fire = firerate;
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (fire <= 0)
		{
			fire = firerate;
			GameObject bull = Instantiate(enemyBullet, firePosition.position, transform.rotation);
			bull.GetComponent<Rigidbody2D>().AddForce(transform.up * shootforce);
		}
		else
			fire -= Time.deltaTime;
	}
}
